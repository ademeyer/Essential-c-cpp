#include <bits/stdc++.h>
using namespace std;

/*
There are N buckets arranged in a row. Each bucket either is empty or contains a ball. The

buckets are specified as a string buckets consisting of characters *.* (empty bucket) and "8"
(bucket with ball). For example, for buckets = 8. BB.B. .B" the row of buckets appears as
follows:

In one move you can take the ball out of any bucket and place itin another (empty) bucket. Your
goal is to arrange the balls to create an alternating sequence of full and empty buckets. In other
words, the distance between two consecutive balls should be equal to 2. Note that the sequence
‘may start at any bucket.

For example, in the figure below, the balls are placed correctly:
*/

int ballBucketArrangement(const string &buckets)
{
  const int n = buckets.size();
  int k = count(buckets.begin(), buckets.end(), 'B');
  int dot = count(buckets.begin(), buckets.end(), '.');

  if (dot < k - 1)
    return -1;

  if (k == 0)
    return 0;
  vector<int> even, odd;
  for (int i = 0; i < n; ++i)
  {
    if (i % 2 == 0)
      even.push_back(buckets[i] == 'B' ? 1 : 0);
    else
      odd.push_back(buckets[i] == 'B' ? 1 : 0);
  }

  int nEven = even.size();
  int nOdd = odd.size();
  // cout << "nEven: " << nEven << " nOdd: " << nOdd << endl;
  vector<int> preEven(nEven + 1, 0), preOdd(nOdd + 1, 0);

  for (int i = 0; i < nEven; ++i)
    preEven[i + 1] = preEven[i] + even[i];
  for (int i = 0; i < nOdd; ++i)
    preOdd[i + 1] = preOdd[i] + odd[i];

  int maxCorrect = 0;
  // Iterate over all possible starting indices i in the original string
  for (int i = 0; i < n; i++)
  {
    int last = i + 2 * (k - 1);
    if (last >= n)
      break;

    if (i % 2 == 0)
    {
      int startIndexInE = i / 2;
      int endIndexInE = startIndexInE + k - 1;
      if (endIndexInE < nEven)
      {
        int correct = preEven[endIndexInE + 1] - preEven[startIndexInE];
        if (correct > maxCorrect)
        {
          maxCorrect = correct;
        }
      }
    }
    else
    {
      int startIndexInO = (i - 1) / 2;
      int endIndexInO = startIndexInO + k - 1;
      if (endIndexInO < nOdd)
      {
        int correct = preOdd[endIndexInO + 1] - preOdd[startIndexInO];
        if (correct > maxCorrect)
        {
          maxCorrect = correct;
        }
      }
    }
  }

  return k - maxCorrect;
}

int main()
{
  auto r = ballBucketArrangement("..B....B.BB"); // Expects 2, Got 2
  cout << "result: " << r << endl;
  r = ballBucketArrangement("BB.B.BBB..."); // Expects 4, got 5
  cout << "result: " << r << endl;
  r = ballBucketArrangement(".BBB.B"); // Expects -1, got 4
  cout << "result: " << r << endl;
  r = ballBucketArrangement("......B.B"); // Expects 0, got 0
  cout << "result: " << r << endl;
  return 0;
}
