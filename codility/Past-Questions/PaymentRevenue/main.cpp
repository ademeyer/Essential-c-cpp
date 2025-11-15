#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int solution(vector<int> &A)
{
  int reloc = 0;
  LL cur_sum = 0;
  /* min - heap to store negative integers */
  priority_queue<int, vector<int>, greater<int>> pq;

  for (const auto &num : A)
  {
    cur_sum += num;
    if (num < 0)
      pq.push(num);

    if (cur_sum < 0)
    {
      /* relocate the most negative number */
      int m = pq.top();
      pq.pop();
      cur_sum -= m;
      ++reloc;
    }
  }
  return reloc;
}

int main()
{
  vector<int> A = {10, -10, -1, -1, 10}; // 1
  cout << "Best financial move: " << solution(A) << endl;
  A = {-1, -1, -1, 1, 1, 1, 1}; // 3
  cout << "Best financial move: " << solution(A) << endl;
  A = {5, -2, -3, 1}; // 0
  cout << "Best financial move: " << solution(A) << endl;

  return 0;
}