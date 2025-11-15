#include <iostream>
#include <vector>
#include <string>
#include <format>

class num 
{
  std::vector<int> n;
  public:
    /* Constructor */
    num(const std::vector<int>& i = {}) : n(i.begin(), i.end()) { std::cout << "ctor\n"; }
    /* Copy constructor */
    num(const num& rhs) : n(rhs.n.begin(), rhs.n.end()) { std::cout << "copy ctor\n"; }
    /* Move constructor */
    num(num&& rhs) noexcept : n(std::move(rhs.n)) { std::cout << "move ctor\n"; }
    /* Copy/Swap assignment operator */
    num& operator=(num rhs) noexcept
    {
      std::cout << "copy/swap assignment\n";
      if(this != &rhs) std::swap(n, rhs.n);
      return *this;
    }

    operator std::string() const 
    {
      if(n.empty()) return "empty";
      std::string res = "{ ";
      for(const auto e : n)
        res += std::to_string(e) + " ";
      res += "}";
      return res;
    }
};

int main()
{
  std::vector<int> n = {1,2,4,5};
  num n1(n);
  num n2 = n1;
  num n3;
  n3 = std::move(n1);
  std::cout << std::vformat(
      std::string_view("n1: {}, n2: {}, n3: {}\n"), 
      std::make_format_args(
        std::string(n1),
        std::string(n2),
        std::string(n3)
        ));
  return 0;
}
