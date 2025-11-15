#include <bits/stdc++.h>
using namespace std;
/*
You are given a string S consisting of letters ‘a’ and/or 'b'. A block is a consecutive fragment of
S composed of the same letters and surrounded by different letters or string endings. For
example, S = "abbabbaaa” has five blocks: "a", "bb, "a", "bb" and "aaa.

What is the minimum number of additional letters needed to obtain a string containing blocks
of equal lengths? Letters can be added at the beginning, between two existing letters, or at the
end of the string.

Write a function:

int solution(string &5);

that, given a string S of length N, returns the minimum number of additional letters needed to
obtain a string containing blocks of equal lengths.

Examples:

1. Given S = "babaa’, the function should return 3. There are four blocks: "b", "a",
letter each should be added to the first, second and third blocks, therefore obtaining a string
*bbaabbaa’, in which every block is of equal length.

2. Given S = "bbbab?, the function should return 4. Two letters each should be added to the
second and third blocks, therefore obtaining a string "bbbaaabbb?, in which every block is of
equal length.

3. Given S = "bbbaaabbb", the function should return 0. All blocks are already of equal lengths.
Write an efficient algorithm for the following assumptions:

« Nis an integer within the range [1..40,000];
« string S consists only of the characters "a" and/or "b".
*/

int minLetter(const string &S)
{
  const int n = S.length();
  if (n == 0)
    return 0;

  vector<int> blockLen;
  int curLen = 1;
  for (int i = 1; i < n; ++i)
  {
    if (S[i] == S[i - 1])
      ++curLen;
    else
    {
      blockLen.push_back(curLen);
      curLen = 1;
    }
  }

  blockLen.push_back(curLen);

  // for (const auto &a : blockLen)
  //   cout << a << ", ";
  // cout << endl;

  int MaxBlock = *max_element(blockLen.begin(), blockLen.end());
  int neededLetters = 0;
  for (const auto &len : blockLen)
    neededLetters += (MaxBlock - len);

  return neededLetters;
}

int main()
{
  cout << "Min Letters: " << minLetter("abbabbaaa") << endl;
  cout << "Min Letters: " << minLetter("babaa") << endl;
  cout << "Min Letters: " << minLetter("bbbab") << endl;
  cout << "Min Letters: " << minLetter("bbbaaabbb") << endl;

  return 0;
}