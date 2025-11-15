#include <bits/stdc++.h>
#include <string>
using namespace std;

int solution(int N)
{
  string s = to_string(N);

  if (N >= 0)
  {
    for (int i = 0; i < s.size(); ++i)
    {
      if (s[i] < '5')
      {
        s.insert(i, "5");
        return stoi(s);
      }
    }
    s += '5';
    return stoi(s);
  }
  else
  {
    for (int i = 1; i < s.size(); ++i)
    {
      if (s[i] > '5')
      {
        s.insert(i, "5");
        return stoi(s);
      }
    }
    s += '5';
    return stoi(s);
  }
}

int main()
{
  cout << "Max Possible: " << solution(268) << endl;  // 5268
  cout << "Max Possible: " << solution(670) << endl;  // 6750
  cout << "Max Possible: " << solution(0) << endl;    // 50
  cout << "Max Possible: " << solution(-999) << endl; // -5999

  return 0;
}