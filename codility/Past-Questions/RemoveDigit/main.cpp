#include <bits/stdc++.h>
using namespace std;

int removeDigit(int N)
{
  string s = to_string(N);
  const int n = s.size();
  int last_occurrence = -1;

  if (N >= 0)
  {
    for (int i = 0; i < n; ++i)
    {
      for (int i = 0; i < n; ++i)
      {
        if (s[i] == '5')
        {
          if (i < n - 1 && s[i + 1] > '5')
          {
            last_occurrence = i;
            break;
          }
          last_occurrence = i;
        }
      }
    }
  }
  else
  {
    for (int i = 1; i < n; ++i)
    {
      if (s[i] == '5')
      {
        if (i < n - 1 && s[i + 1] < '5')
        {
          last_occurrence = i;
          break;
        }
        last_occurrence = i;
      }
    }
  }
  /* slice and rejoin number string */
  string num_str = s.substr(0, last_occurrence) + s.substr(last_occurrence + 1);

  if (num_str.empty() || num_str == "0" || num_str == "-0")
    return 0;

  return stoi(num_str);
}

int main()
{
  cout << "maximum possible value: " << removeDigit(15958) << endl; // 1958
  cout << "maximum possible value: " << removeDigit(-5859) << endl; // -589
  cout << "maximum possible value: " << removeDigit(-5000) << endl; // 0

  return 0;
}
