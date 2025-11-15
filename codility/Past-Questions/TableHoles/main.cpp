#include <bits/stdc++.h>
using namespace std;

bool feasible(const vector<int> &A, int L)
{
  int n = A.size();
  // First board starts at A[0] and covers up to A[0] + L.
  int idx = 0;
  while (idx < n && A[idx] - A[0] <= L)
  {
    idx++;
  }
  // If all holes are covered by the first board, return true.
  if (idx >= n)
    return true;
  // Check if the second board can cover the remaining holes: from A[idx] to A[n-1].
  return (A[n - 1] - A[idx] <= L);
}

int solution(vector<int> &A)
{
  sort(A.begin(), A.end());
  int n = A.size();
  if (n <= 2)
    return 1; // Because with two boards of length 1, we can cover two holes.

  int low = 1;
  int high = A[n - 1] - A[0];
  int ans = high;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (feasible(A, mid))
    {
      ans = mid;
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  return ans;
}

int main()
{
  vector<int> A1 = {11, 20, 15};
  cout << solution(A1) << endl; // should be 4.

  vector<int> A2 = {15, 20, 9, 11};
  cout << solution(A2) << endl; // should be 5.

  vector<int> A3 = {0, 44, 32, 30, 42, 18, 34, 16, 35};
  cout << solution(A3) << endl; // 18.

  vector<int> A4 = {9};
  cout << solution(A4) << endl; // 1.

  return 0;
}