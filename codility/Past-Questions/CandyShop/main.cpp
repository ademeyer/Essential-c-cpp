#include <bits/stdc++.h>
using namespace std;

int maxDifferentTypes(int N, vector<int> &shop1,
                      vector<int> &shop2)
{
  unordered_set<int> distinctTypes;
  for (const auto &t : shop1)
    distinctTypes.insert(t);
  for (const auto &t : shop2)
    distinctTypes.insert(t);

  int T = distinctTypes.size();
  return min(T, N);
}

int main()
{

  return 0;
}