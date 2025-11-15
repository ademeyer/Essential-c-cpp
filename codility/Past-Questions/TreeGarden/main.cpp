#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> &trees)
{
  auto isAesthetic = [&](const vector<int> &trees, int excludeIndex) -> bool
  {
    const int n = trees.size();
    for (int i = 0; i < n - 2; ++i)
    {
      /* Skip triplet indices that is excluded */
      if (i == excludeIndex || i + 1 == excludeIndex || i + 2 == excludeIndex)
        continue;

      if (i + 1 == excludeIndex)
        continue;
    }
    vector<int> noExclude;
    for (int i = 0; i < n; ++i)
    {
      if (i != excludeIndex)
        noExclude.push_back(trees[i]);
    }
    int m = noExclude.size();
    for (int i = 0; i < m - 2; ++i)
    {
      if (!((noExclude[i] < noExclude[i + 1] &&
             noExclude[i + 1] > noExclude[i + 2]) ||
            noExclude[i] > noExclude[i + 1] &&
                noExclude[i + 1] < noExclude[i + 2]))
        return false;
    }
    return true;
  };

  const int n = trees.size();
  if (isAesthetic(trees, -1))
    return 0;

  int cnt = 0;
  for (int i = 0; i < n; ++i)
  {
    if (isAesthetic(trees, i))
      ++cnt;
  }
  if (cnt == 0)
    return -1;

  return cnt;
}

int main()
{
  vector<int> trees = {3, 4, 5, 3, 7}; // 3
  cout << "No of ways to make aesthetic: " << solution(trees) << endl;

  trees = {1, 2, 3, 4}; // -1
  cout << "No of ways to make aesthetic: " << solution(trees) << endl;
  trees = {1, 3, 1, 2}; // 0
  cout << "No of ways to make aesthetic: " << solution(trees) << endl;

  return 0;
}
