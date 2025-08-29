#include <string>
#include <iostream>
using namespace std;

string solution(string S, string T)
{
  int n = S.size();
  int m = T.size();

  if (S == T)
  {
    return "EQUAL";
  }

  // Check for INSERT
  if (m - n == 1)
  {
    if (T.substr(1) == S)
    {
      return "INSERT " + string(1, T[0]);
    }
  }

  // Check for REMOVE
  if (n - m == 1)
  {
    if (S.substr(0, n - 1) == T)
    {
      return "REMOVE " + string(1, S[n - 1]);
    }
  }

  // Check for SWAP
  if (n == m)
  {
    for (int i = 0; i < n - 1; i++)
    {
      if (S[i] != T[i])
      {
        // Check if swapping i and i+1 in S gives T
        if (S[i] == T[i + 1] && S[i + 1] == T[i] && S[i] != S[i + 1])
        {
          string swapped = S;
          swap(swapped[i], swapped[i + 1]);
          if (swapped == T)
          {
            return "SWAP " + string(1, S[i]) + " " + string(1, S[i + 1]);
          }
        }
        break; // Only one mismatch allowed, so break after first mismatch
      }
    }
  }

  return "IMPOSSIBLE";
}

int main()
{
  cout << solution("gain", "again") << endl; // "INSERT a"
  cout << solution("parks", "park") << endl; // "REMOVE s"
  cout << solution("form", "from") << endl;  // "SWAP o r"
  cout << solution("o", "odd") << endl;      // "IMPOSSIBLE"
  return 0;
}