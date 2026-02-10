#include <iostream>
#include <vector>

class NumberIterator
{
public:
  virtual ~NumberIterator() {}
  virtual int next() = 0;
  virtual bool isFinished() = 0;
};

class ForwardsIterator : public NumberIterator
{
  int currentPosition;
  std::vector<int> &numbers;

public:
  ForwardsIterator(std::vector<int> &num) : numbers(num), currentPosition(0) {}
  int next() override
  {
    int current = numbers.at(currentPosition);
    ++currentPosition;
    return current;
  }
  bool isFinished() override { return currentPosition == numbers.size(); }
};

class BackwardsIterator : public NumberIterator
{
  int currentPosition;
  std::vector<int> &numbers;

public:
  BackwardsIterator(std::vector<int> &num) : numbers(num), currentPosition(0) {}
  int next() override
  {
    int current = numbers.at(numbers.size() - currentPosition - 1);
    ++currentPosition;
    return current;
  }
  bool isFinished() override { return currentPosition == numbers.size(); }
};

class NumberCollection
{
  std::vector<int> numbers;

public:
  NumberCollection(const std::vector<int> &num) : numbers(num) {}
  NumberIterator *getForwardsIterator() { return new ForwardsIterator(numbers); }
  NumberIterator *getBackwardsIterator() { return new BackwardsIterator(numbers); }
};

int main()
{
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7};
  NumberCollection nc(numbers);
  NumberIterator *fi = nc.getForwardsIterator();
  NumberIterator *bi = nc.getBackwardsIterator();

  while (!fi->isFinished())
    std::cout << fi->next() << ", ";

  std::cout << std::endl
            << "Iterating through the numbers backwards: \n";
  while (!bi->isFinished())
    std::cout << bi->next() << ", ";

  std::cout << std::endl;

  delete fi;
  delete bi;

  return 0;
}