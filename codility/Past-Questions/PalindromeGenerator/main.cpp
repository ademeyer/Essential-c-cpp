#include <bits/stdc++.h>
using namespace std;

string solution(int N, int K)
{
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  int halfLength = (N + 1) / 2;
  string firstHalf;

  // Use the first K distinct letters
  for (int i = 0; i < min(K, halfLength); i++)
  {
    firstHalf += alphabet[i];
  }

  // If we have more positions in the first half than K, fill the rest with the last distinct letter
  for (int i = K; i < halfLength; i++)
  {
    firstHalf += alphabet[K - 1];
  }

  // Build the full palindrome
  string palindrome = firstHalf;
  for (int i = N / 2 - 1; i >= 0; i--)
  {
    palindrome += firstHalf[i];
  }

  return palindrome;
}

int main()
{
  cout << "Palindrome: " << solution(5, 2) << endl;
  cout << "Palindrome: " << solution(8, 3) << endl;
  cout << "Palindrome: " << solution(3, 2) << endl;

  return 0;
}
