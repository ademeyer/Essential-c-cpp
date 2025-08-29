#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll compute_actions(const vector<ll> &A, const vector<ll> &prefix, ll T)
{
  int n = A.size();
  // Find the first index where A[i] > T
  int idx = upper_bound(A.begin(), A.end(), T) - A.begin();
  ll surplus = 0;
  if (idx < n)
  {
    surplus = (prefix[n] - prefix[idx]) - T * (n - idx);
  }
  ll planting = T * n - prefix[n];
  return planting + surplus;
}

ll solution(vector<int> &A)
{
  int n = A.size();
  if (n == 0)
    return 0;
  vector<ll> A_long(A.begin(), A.end());
  sort(A_long.begin(), A_long.end());
  vector<ll> prefix(n + 1, 0);
  for (int i = 0; i < n; i++)
  {
    prefix[i + 1] = prefix[i] + A_long[i];
  }
  ll total_trees = prefix[n];
  ll low = (total_trees + n - 1) / n; // ceiling of total_trees/n
  ll high = A_long.back();
  ll ans = LLONG_MAX;

  // Ternary search
  while (high - low > 2)
  {
    ll mid1 = low + (high - low) / 3;
    ll mid2 = high - (high - low) / 3;
    ll f1 = compute_actions(A_long, prefix, mid1);
    ll f2 = compute_actions(A_long, prefix, mid2);
    if (f1 < f2)
    {
      high = mid2;
    }
    else
    {
      low = mid1;
    }
  }
  for (ll T = low; T <= high; T++)
  {
    ans = min(ans, compute_actions(A_long, prefix, T));
  }
  return ans;
}

int main()
{
  vector<int> A1 = {1, 2, 2, 4};
  cout << solution(A1) << endl; // 4

  vector<int> A2 = {4, 2, 4, 6};
  cout << solution(A2) << endl; // 2

  vector<int> A3 = {1, 1, 2, 1};
  cout << solution(A3) << endl; // 3

  return 0;
}