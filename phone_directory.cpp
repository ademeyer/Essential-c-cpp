#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string findContact(std::vector<std::string> &names,
                        std::vector<std::string> &numbers, std::string search_str)
{
  std::vector<std::pair<std::string, std::string>> matches;

  // Check each contact
  for (int i = 0; i < names.size(); ++i)
  {
    // check if search_str appears anywhere in the number
    if (numbers[i].find(search_str) != std::string::npos)
      matches.push_back({names[i], numbers[i]});
  }

  // If no matched found
  if (matches.empty())
    return "NO CONTACT";

  std::sort(matches.begin(), matches.end(),
            [](const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b)
            {
              return a.first < b.first;
            });

  return matches[0].first;
}

int main()
{
  // Test Case 1
  std::vector<std::string> names1 = {"pim", "pom"};
  std::vector<std::string> numbers1 = {"999999999", "777888999"};
  std::string search1 = "88999";
  std::cout << "Test 1: " << findContact(names1, numbers1, search1) << std::endl; // Expected: pom

  // Test Case 2
  std::vector<std::string> names2 = {"sander", "amy", "ann", "michael"};
  std::vector<std::string> numbers2 = {"123456789", "234567890", "789123456", "123123123"};
  std::string search2 = "1";
  std::cout << "Test 2: " << findContact(names2, numbers2, search2) << std::endl; // Expected: ann

  // Test Case 3
  std::vector<std::string> names3 = {"adam", "eva", "leo"};
  std::vector<std::string> numbers3 = {"121212121", "111111111", "444555666"};
  std::string search3 = "112";
  std::cout << "Test 3: " << findContact(names3, numbers3, search3) << std::endl; // Expected: NO CONTACT

  return 0;
}