#include <bits/stdc++.h>
using namespace std;

vector<int> solution(int N, vector<int> &A)
{
  vector<int> counters(N, 0);
  int cnt_max = 0;
  int cnt = 0;

  for (const auto &op : A)
  {
    if (op >= 1 && op <= N)
    {
      int idx = op - 1;
      /* If this counter hasn't been updated after the last max operation */
      if (counters[idx] < cnt)
        counters[idx] = cnt + 1;
      else
        counters[idx]++;

      /* Update cnt_max if needed */
      cnt_max = max(cnt_max, counters[idx]);
    }
    else if (op == N + 1)
    {
      /* Instead of updating all counters, just update the base counter */
      cnt = cnt_max;
    }
  }

  /* Finally, ensure all counters are at least cnt */
  for (int i = 0; i < N; ++i)
    counters[i] = max(counters[i], cnt);

  return counters;
}

int main()
{
  vector<int> A = {3, 4, 4, 6, 1, 4, 4};
  int N = 5;
  auto res = solution(N, A);
  for (const auto &i : res)
    cout << i << ", ";
  cout << "\n";
  return 0;
}