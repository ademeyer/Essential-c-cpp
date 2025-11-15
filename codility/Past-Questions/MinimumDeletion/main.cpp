#include <bits/stdc++.h>
using namespace std;

int minDeletion(string s)
{
  unordered_map<char, int> freqMap;
  for (char c : s)
    freqMap[c]++;

  vector<int> frequencies;
  for (const auto &pair : freqMap)
    frequencies.push_back(pair.second);

  sort(frequencies.rbegin(), frequencies.rend());
  int del = 0;
  int maxAllowed = frequencies[0];
  for (int i = 0; i < frequencies.size(); ++i)
  {
    if (frequencies[i] > maxAllowed)
    {
      del += frequencies[i] - maxAllowed;
      frequencies[i] = maxAllowed;
    }
    if (maxAllowed > 0)
      maxAllowed = frequencies[i] - 1;
    else
    {
      del += frequencies[i];
      frequencies[i] = 0;
    }
  }
  return del;
}

int main()
{
  cout << minDeletion("aab") << endl;      // Output: 0
  cout << minDeletion("aaabbbcc") << endl; // Output: 2
  cout << minDeletion("ceabaacb") << endl; // Output: 2

  return 0;
}