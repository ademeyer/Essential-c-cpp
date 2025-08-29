#include <bits/stdc++.h>
using namespace std;

bool isBalanced(const unordered_map<char, int> &freq)
{
  for (const auto &entry : freq)
  {
    char c = entry.first;
    if (isalpha(c))
    {
      char oppositeCase = islower(c) ? toupper(c) : tolower(c);
      if (freq.find(oppositeCase) == freq.end() || freq.at(oppositeCase) == 0)
      {
        return false;
      }
    }
  }
  return true;
}

string shortestBalancedSubstring(string s)
{
  int n = s.size();
  int minLen = INT_MAX;
  string result = "";

  for (int i = 0; i < n; i++)
  {
    unordered_map<char, int> freq;
    for (int j = i; j < n; j++)
    {
      freq[s[j]]++;
      if (isBalanced(freq))
      {
        int len = j - i + 1;
        if (len < minLen)
        {
          minLen = len;
          result = s.substr(i, len);
        }
      }
    }
  }

  return minLen == INT_MAX ? "-1" : result;
}

int main()
{
  cout << shortestBalancedSubstring("azABaabza") << endl; // Output: "ABaab"
  cout << shortestBalancedSubstring("TacoCat") << endl;   // Output: "-1"
  cout << shortestBalancedSubstring("AcZCbaBz") << endl;  // Output: "AcZCbaBz"

  return 0;
}