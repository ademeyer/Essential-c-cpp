#include <bits/stdc++.h>

using namespace std;
using ULL = unsigned long long;


// Fibonacci function with Memoization Optimization
ULL fib(int num)
{
  unordered_map<int, ULL> cache = 
  {
    { 0, 0 },
    { 1, 1 },
    { 2, 1 },
  };

  function<ULL(int)> f = [&](int n) -> ULL
  {
    if(n <= 1) return n;

    if(cache.find(n) != cache.end())
      return cache[n];

    auto ans = f(n - 1) + f(n - 2);
    cache[n] = ans;
    return ans;
  };
  
  return f(num);
}

void wrapper(ULL num, ULL& result)
{
  result = fib(num);
}

const int NUM = 500;

int main(int argc, char* argv[])
{
  auto start = chrono::steady_clock::now();

  auto res = fib(NUM);

  const auto timeTaken = chrono::steady_clock::now() - start;

  cout << "fib(" << NUM << "): " << res 
          << "\ntime elapsed: " << timeTaken.count() / 1000.00
                << "ms" << endl;
  return 0;
}
