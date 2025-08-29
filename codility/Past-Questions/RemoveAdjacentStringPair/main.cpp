#include <bits/stdc++.h>
using namespace std;

string solution(string S)
{
  stack<char> st;
  for (char c : S)
  {
    if (!st.empty())
    {
      char top = st.top();
      if ((top == 'A' && c == 'B') || (top == 'B' && c == 'A') ||
          (top == 'C' && c == 'D') || (top == 'D' && c == 'C'))
      {
        st.pop();
        continue;
      }
    }
    st.push(c);
  }

  string result;
  while (!st.empty())
  {
    result = st.top() + result;
    st.pop();
  }
  return result;
}

int main()
{
  cout << solution("CBACD") << endl;    // "C"
  cout << solution("CABABD") << endl;   // ""
  cout << solution("ACBDACBD") << endl; // "ACBDACBD"
  return 0;
}