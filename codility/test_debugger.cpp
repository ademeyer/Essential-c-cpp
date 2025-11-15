#include <bits/stdc++.h>

class Battery
{
};

template <typename T>
T findLargest(std::vector<T> numbers)
{
  assert(!numbers.empty());
  auto largest = std::numeric_limits<T>::min();

  for (auto it = std::begin(numbers); it != std::end(numbers); ++it)
    largest = *it > largest ? *it : largest;
  return largest;
}

int main()
{
  int value = 45;
  std::cout << "we want to debug: " << value << std::endl;
  std::vector<int> numbers = {7, 27, -3, 9, 11};
  std::cout << "largest number: " << findLargest(numbers) << std::endl;
  return 0;
}