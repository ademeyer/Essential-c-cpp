#include <iostream>
#include <string>
#include <vector>

std::string formatPhoneNumber(const std::string &s)
{
  std::string digits;
  for (const auto &c : s)
  {
    if (std::isdigit(c))
      digits += c;
  }

  int n = digits.size();
  std::string result = "";
  int i = 0;

  // edge condition
  if (n <= 3)
    return digits;

  // determine the pattern
  int remainder = n % 3;
  int read_last = 0;

  if (remainder == 0)
    read_last = n;
  else if (remainder == 1)
    read_last = n - 4;
  else
    read_last = n - 2;

  for (i = 0; i < read_last; i += 3)
  {
    if (!result.empty())
      result += "-";
    result += digits.substr(i, 3);
  }

  // remaining the group of 2s
  if (remainder != 0)
  {
    for (i; i < n; i += 2)
    {
      if (!result.empty())
        result += "-";
      result += digits.substr(i, 2);
    }
  }

  return result;
}

int main()
{
  std::cout << formatPhoneNumber("123456") << std::endl;     // 123-456
  std::cout << formatPhoneNumber("1234567") << std::endl;    // 123-45-67
  std::cout << formatPhoneNumber("12345678") << std::endl;   // 123-456-78
  std::cout << formatPhoneNumber("123456789") << std::endl;  // 123-456-789
  std::cout << formatPhoneNumber("1234567890") << std::endl; // 123-456-78-90

  return 0;
}