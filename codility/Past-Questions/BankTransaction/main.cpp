#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> &A, vector<string> &D)
{
  map<int, int> income;
  map<int, int> payments;
  map<int, int> count;

  const int n = A.size();
  for (int i = 0; i < n; ++i)
  {
    int amt = A[i];
    string date = D[i];
    int month = stoi(date.substr(5, 2)); // Extract MM, from YYYY-MM-DD

    if (amt < 0)
    {
      payments[month] += -amt;
      count[month]++;
    }
    else
    {
      income[month] += amt;
    }
  }

  int total_income = 0;
  int total_payments = 0;
  for (int i = 0; i < n; ++i)
    total_income += A[i];

  int fee = 0;
  for (int month = 1; month <= 12; ++month)
  {
    if (count[month] < 3 || payments[month] < 100)
      fee += 5;
  }

  return total_income - fee;
}

int main()
{
  vector<int> A = {100, 100, 100, -10};
  vector<string> D = {"2020-12-31", "2020-12-22", "2020-12-03", "2020-12-29"};
  cout << "transaction: " << solution(A, D) << endl;
  return 0;
}