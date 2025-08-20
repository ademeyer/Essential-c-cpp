#include <bits/stdc++.h>

int main()
{
  std::string a = "Hello";
  std::string b = "";
  std::cout << "size_a: " << a.size() << 
    " size_b: " << b.size() << std::endl;
  b = std::move(a);
  std::cout << "size_a: " << a.size() <<
    " size_b: " << b.size() << std::endl;

  return 0;
}
