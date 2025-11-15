#include <bits/stdc++.h>
using namespace std;

int minStepsToEqual(vector<int> &arr)
{
  /* We can also use sort here */
  sort(arr.begin(), arr.end());

  const int n = arr.size();
  int med = arr[n / 2];
  int step = 0;
  for (const auto &n : arr)
    step += abs(n - med);

  return step;
}

int main()
{
  vector<int> arr = {1, 3, 2, 4};
  cout << "minmum steps to make equal: " << minStepsToEqual(arr) << endl;

  arr = {1, 2, 3};
  cout << "minmum steps to make equal: " << minStepsToEqual(arr) << endl;

  arr = {1, 10, 2, 9};
  cout << "minmum steps to make equal: " << minStepsToEqual(arr) << endl;

  return 0;
}