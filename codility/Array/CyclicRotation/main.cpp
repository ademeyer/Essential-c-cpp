#include <bits/stdc++.h>
using namespace std;
/*

An array A consisting of N integers is given. Rotation of the array means that each element is shifted right by one index, and the last element of the array is moved to the first place. For example, the rotation of array A = [3, 8, 9, 7, 6] is [6, 3, 8, 9, 7] (elements are shifted right by one index and 6 is moved to the first place).

The goal is to rotate array A K times; that is, each element of A will be shifted to the right K times.

Write a function:

vector<int> solution(vector<int> &A, int K);

that, given an array A consisting of N integers and an integer K, returns the array A rotated K times.

For example, given

    A = [3, 8, 9, 7, 6]
    K = 3
the function should return [9, 7, 6, 3, 8]. Three rotations were made:

    [3, 8, 9, 7, 6] -> [6, 3, 8, 9, 7]
    [6, 3, 8, 9, 7] -> [7, 6, 3, 8, 9]
    [7, 6, 3, 8, 9] -> [9, 7, 6, 3, 8]
For another example, given

    A = [0, 0, 0]
    K = 1
the function should return [0, 0, 0]

Given

    A = [1, 2, 3, 4]
    K = 4
the function should return [1, 2, 3, 4]

Assume that:

N and K are integers within the range [0..100];
each element of array A is an integer within the range [−1,000..1,000].
In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.
*/

void printvec(const vector<int> &v)
{
  cout << "[";
  for (const auto i : v)
    cout << i << ", ";
  cout << "]\n";
}

vector<int> solution(vector<int> &A, int K)
{
  int n = A.size();

  // Edge cases
  if (n == K || n == 0 || K == 0)
    return A;
  // Manage overflow
  K = K % n;
  bool popBack = true;
  int L = n - K;
  int shiftPos = 0;
  // A = [3, 8, 9, 7, 6]
  /* We want to know where to rotate the array
  by checking minimum rotate */
  popBack = (K < L);
  shiftPos = popBack ? K : L;
  vector<int> vec(shiftPos, 0);
  for (int i = 0; i < shiftPos; ++i)
  {
    if (popBack)
    {
      vec[shiftPos - 1 - i] = A[A.size() - 1];
      A.erase(A.begin() + (A.size() - 1)); // pop_back
    }
    else
    {
      vec[i] = A[0];
      A.erase(A.begin()); // pop_front
    }
  }
  if (popBack)
    vec.insert(vec.end(), make_move_iterator(A.begin()),
               make_move_iterator(A.end()));
  else
    vec.insert(vec.begin(), make_move_iterator(A.begin()),
               make_move_iterator(A.end()));
  return vec;
}

int main()
{
  vector<int> A = {3, 8, 9, 7, 6};
  int K = 3;
  auto res = solution(A, K);
  printvec(res);

  A = {0, 0, 0};
  K = 1;
  res = solution(A, K);
  printvec(res);

  A = {1, 2, 3, 4};
  K = 4;
  res = solution(A, K);
  printvec(res);

  A = {1, 2, 3, 4};
  K = 5;
  res = solution(A, K);
  printvec(res);

  return 0;
}