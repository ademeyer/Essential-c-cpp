#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> &A)
{
  const int n = A.size();
  int initial = 0;
  for (int i = 0; i < n - 1; ++i)
  {
    if (A[i] == A[i + 1])
      ++initial;
  }

  int maxPossible = 0;
  for (int i = 0; i < n; ++i)
  {
    int change = 0;
    if (i > 0)
    {
      if (A[i] == A[i - 1])
        --change;
      else
        ++change;
    }
    if (i < n - 1)
    {
      if (A[i] == A[i + 1])
        --change;
      else
        ++change;
    }
    maxPossible = max(maxPossible, change);
  }

  return initial + maxPossible;
}

int main()
{
  vector<int> A = {1, 1, 0, 1, 0, 0};
  cout << "Max coin: " << solution(A) << endl;
  return 0;
}