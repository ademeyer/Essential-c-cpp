#include <bits/stdc++.h>
using namespace std;

struct CharCount
{
  int count;
  char letter;
  CharCount(int c, char l) : count(c), letter(l) {}
  bool operator<(const CharCount &other) const
  {
    return count < other.count;
  }
};

string solution(int A, int B, int C)
{
  priority_queue<CharCount> pq;
  if (A > 0)
    pq.push(CharCount(A, 'a'));
  if (B > 0)
    pq.push(CharCount(B, 'b'));
  if (C > 0)
    pq.push(CharCount(C, 'c'));

  string result;
  while (!pq.empty())
  {
    CharCount first = pq.top();
    pq.pop();
    int n = result.size();
    // Check if the last two characters are the same as first.letter
    if (n >= 2 && result[n - 1] == first.letter && result[n - 2] == first.letter)
    {
      if (pq.empty())
        break;
      CharCount second = pq.top();
      pq.pop();
      result += second.letter;
      second.count--;
      if (second.count > 0)
        pq.push(second);
      pq.push(first);
    }
    else
    {
      result += first.letter;
      first.count--;
      if (first.count > 0)
        pq.push(first);
    }
  }
  return result;
}

int main()
{
  cout << solution(6, 1, 1) << endl; // Example 1
  cout << solution(1, 3, 1) << endl; // Example 2
  cout << solution(0, 1, 8) << endl; // Example 3
  return 0;
}