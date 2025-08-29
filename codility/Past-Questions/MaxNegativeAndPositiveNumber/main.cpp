#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> &A)
{
  unordered_set<int> seen;
  int maxK = 0;
  for (const auto &num : A)
  {
    if (seen.find(-num) != seen.end())
    {
      int can = abs(num);
      if (can > maxK)
        maxK = can;
    }
    seen.insert(num);
  }
  return maxK;
}

int main()
{
  vector<int> A = {3, 2, -2, 5, -3};
  cout << "max negative and positive element: " << solution(A) << endl;
  A = {1, 1, 2, -1, 2, -1};
  cout << "max negative and positive element: " << solution(A) << endl;
  A = {1, 2, 3, -4};
  cout << "max negative and positive element: " << solution(A) << endl;

  return 0;
}