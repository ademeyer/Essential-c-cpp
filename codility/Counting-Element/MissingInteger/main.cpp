#include <bits/stdc++.h>
using namespace std;
/*
Write a function:

int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
*/
int findMissingInteger(vector<int> &A)
{
  if (A.empty())
    return 1;
  unordered_set<int> cache;
  int min_element = INT_MAX;
  for (const auto &a : A)
  {
    min_element = min(min_element, a);
    cache.insert(a);
  }
  /* A non negative integer that is greater than 1 */
  if (min_element > 1)
    return 1;

  int missing_element = 0, i = 0;
  // 102, 103, 106, 104, 101, 102
  while (i < cache.size())
  {
    /* If we did not find the min_element */
    if (cache.find(min_element) == cache.end())
    {
      /* If the min_element is not a positive integer,
          increment min_element and try again */
      if (min_element <= 0)
      {
        ++min_element;
        continue;
      }
      /* It is a positive, we can grab it and burst out */
      missing_element = min_element;
      break;
    }
    ++min_element;
    ++i;
  }

  /* If we have no success finding min element missing
      and  it's a non positive integer, we should
      pick next positive integer which is 1 */
  if (min_element <= 0)
    missing_element = 1;

  return missing_element == 0 ? min_element : missing_element;
}

int main()
{
  {
    vector<int> A = {102, 103, 106, 104, 101, 102};
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {1, 2, 3};
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {-1, -3};
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {-2, -1, 0, -1, -3, 1, 2}; // 3
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {-2, -1, 0, -1, -3, 1, 3}; // 2
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {-1, 0, -1, -3, 1, 2}; // 3
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {-1, -1, -3, 1, 2}; // 3
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {-3}; // 1
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {1}; // 2
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {0}; // 1
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  {
    vector<int> A = {}; // 1
    cout << "Missing Minimum Element: " << findMissingInteger(A) << "\n";
  }
  return 0;
}