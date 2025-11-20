#include <format>
#include <deque>
#include <thread>
#include <mutex>

constexpr void print(const std::string_view str_fmt, auto&&... args)
{
  fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

using namespace std::chrono_literals;

constexpr size_t num_items {10};
constexpr auto delay_time {250ms};

std::mutex p_mtx {}; // producer mutex
std::mutex c_mtx {}; // consumer mutex
std::deque<size_t> q{};
std::atomic_flag finished {};

void sleep_ms(const auto& delay)
{
  std::this_thread::sleep_for(delay);
}

void producer()
{
  for(size_t i{}; i < num_items; ++i)
  {
    sleep_ms(delay_time);
    print("push {} on the queue\n", i);
    std::lock_guard<std::mutex> lck(p_mtx);
    q.push_back(i);
  }

  std::lock_guard<std::mutex> lck(p_mtx);
  finished.test_and_set();
}

void consumer()
{
  while(!finished.test())
  {
    std::lock_guard<std::mutex> lck(c_mtx);
    while(!q.empty()) 
    {
      print("pop {} from the queue\n", q.front());
      q.pop_front();
    }
  }
}

int main()
{
  std::thread t1{producer};
  std::thread t2{consumer};

  t1.join();
  t2.join();

  print("finished!\n");
  return 0;
}



