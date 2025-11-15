#include <bits/stdc++.h>
using namespace std;

class BadLengthException
{
  int _n;

public:
  BadLengthException(int n)
  {
    _n = n;
  }
  string what()
  {
    return to_string(_n);
  }
};

bool checkUsername(string username)
{
  bool isValid = true;
  int n = username.length();
  if (n < 5)
  {
    throw BadLengthException(n);
  }
  for (int i = 0; i < n - 1; i++)
  {
    if (username[i] == 'w' && username[i + 1] == 'w')
    {
      isValid = false;
    }
  }
  return isValid;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
  {
    string username;
    cin >> username;
    try
    {
      bool isValid = checkUsername(username);
      if (isValid)
      {
        cout << "Valid" << '\n';
      }
      else
      {
        cout << "Invalid" << '\n';
      }
    }
    catch (BadLengthException e)
    {
      cout << "Too short: " << e.what() << '\n';
    }
  }
  return 0;
}