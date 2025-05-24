#include <bits/stdc++.h>
int min_operation(const std::vector<int>& data)
{
    int n = data.size();
    if (n == 0)
        return -1; // Data cannot be empty

    // check if operation is possible
    unsigned long total;
    for(const auto& d : data)
        total += d;

    // check if it is impossible to redistribute energy
    if(total % n != 0)
        return -1; // remainder must be zero

    int op = 0; // operation count
    int even_energy = total / n; // expected energy level for each device

    // get number of operation required to level device energy
    for(const auto& d : data)
        op += std::abs(even_energy - d);

    return op;
}

int main (int argc, char *argv[]) 
{
  std::vector<int> data{2,4,6,8};
  std::cout << "min operation: " << min_operation(data) << std::endl;
  return 0;
}
