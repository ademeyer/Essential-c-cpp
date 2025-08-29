#include <bits/stdc++.h>
using namespace std;

int solution(int N, int K)
{
  int count = 0;
  for (int i = N; i >= 1; i--)
  {
    if (K >= i)
    {
      K -= i;
      count++;
    }
    if (K == 0)
    {
      return count;
    }
  }
  return -1;
}

int main()
{
  cout << "glass needed to fill it: " << solution(5, 8) << endl;
  cout << "glass needed to fill it: " << solution(4, 10) << endl;
  cout << "glass needed to fill it: " << solution(1, 2) << endl;
  cout << "glass needed to fill it: " << solution(10, 5) << endl;

  return 0;
}
