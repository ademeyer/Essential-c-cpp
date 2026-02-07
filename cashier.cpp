#include <vector>
#include <iostream>
#include <queue>

/*
Customers come into a shop. All queued in a single line.
There are 3 cashiers. Next customer goes to the cashier who gets free.
Find when all customers will be done

Input format: Array of tuples

Each item in array is of this form [minutesSinceOpen, durationInMinutes]
minutesSinceOpen - time at which this customer enters
durationInMinutes - time taken by the customer

This needs to be solved completely in 15 minutes
*/

double solve(const std::vector<std::pair<double, double>> &customer)
{
  std::priority_queue<double, std::vector<double>, std::greater<double>> cashier;
  for (int i = 0; i < 3; i++) // 3 - cashier would start at 0.0 workload
    cashier.push(0.0);

  for (const auto &[arrival, duration] : customer)
  {
    // Get Cashier with least workload
    auto freeTime = cashier.top();
    cashier.pop();

    auto new_startTime = std::max(freeTime, arrival);
    auto new_finishTime = duration + new_startTime;

    // return cashier to working position
    cashier.push(new_finishTime);
  }

  double lastTime = 0;
  while (!cashier.empty())
  {
    lastTime = cashier.top();
    cashier.pop();
  }

  return lastTime;
}

int main()
{
  // Example from problem statement? Not given, so let's test with example.
  // Example: customers: [[1, 3], [2, 5], [3, 4], [10, 2]]
  std::vector<std::pair<double, double>> customers = {
      {1, 3},
      {2, 5},
      {3, 4},
      {10, 2}};

  double finish = solve(customers);
  std::cout << "All customers done at: " << finish << std::endl;

  return 0;
}