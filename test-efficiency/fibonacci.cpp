#include <bits/stdc++.h>

using namespace std;
using ULL = unsigned long long;

const size_t MAX_THREADS_NO = 8;

class WorkerThread
{
public:
  WorkerThread(const size_t numthreads = 0)
  {
    const auto n_Threads = numthreads > MAX_THREADS_NO || numthreads == 0 ? MAX_THREADS_NO : numthreads;
    worker.reserve(n_Threads);

    for(int i = 0; i < n_Threads; ++i)
    {
      worker.emplace_back([this](stop_token stoken){
        while(!stoken.stop_requested())
        {
          function<void()> task;
          // Scope block to ensure mutex is release after remove each task
          {
            unique_lock<mutex> lock(q_mtx);
            update.wait(lock, [this, &stoken]{ return !tasks.empty() || stoken.stop_requested(); });
            
            if(stoken.stop_requested())
              break;
            task = move(tasks.front()); tasks.pop();
          }
          // Run task
          task();
        }
      });
    }
  }

  template <class F, class... Args>
  void queueTask(F&& f, Args&&... args)
  {
    const lock_guard<mutex> lock(q_mtx);
    tasks.emplace([f = forward<F>(f), ...args = forward<Args>(args)]() mutable 
                                                { invoke(f, args...); });
    update.notify_one();
  }

  inline bool taskCompleted()
  {
    const lock_guard<mutex> lock(q_mtx);
    return tasks.empty();
  }

  ~WorkerThread()
  {
    for(auto& w : worker)
      w.request_stop();

    // Notify all other tasks in idle state that stop has been requested
    update.notify_all();
  }
private:
  vector<jthread> worker;
  queue<function<void()>> tasks;
  mutex q_mtx;
  condition_variable_any update;
};

// Fibonacci function
ULL fib(ULL num)
{
  return num <= 1 ? num : fib(num - 1) + fib(num - 2);
}

void wrapper(ULL num, ULL& result)
{
  result = fib(num);
}

const int NUM = 50;

int main(int argc, char* argv[])
{
  auto start = chrono::steady_clock::now();
  vector<ULL> results(NUM + 1, 0);

  {
    WorkerThread worker;
    for(int i = 0; i <= NUM; ++i)
      worker.queueTask(wrapper, i, ref(results[i])); 
    
    while(!worker.taskCompleted())
      this_thread::sleep_for(chrono::microseconds(10));
  }

  const auto timeTaken = chrono::steady_clock::now() - start;

  cout << "fib(" << NUM << "): " << results[NUM] 
          << "\ntime elapsed: " << timeTaken.count() / 1000.00
                << "ms" << endl;
  return 0;
}
