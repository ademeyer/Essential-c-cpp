#include <iostream>

class GreetingStrategy
{
public:
  virtual ~GreetingStrategy() {}
  virtual void greet(const std::string &name) = 0;
};

class FormalGreetingStrategy : public GreetingStrategy
{
public:
  void greet(const std::string &name) override { std::cout << "Hello " << name << "!\n"; }
};

class NormalGreetingStrategy : public GreetingStrategy
{
public:
  void greet(const std::string &name) override { std::cout << "Hi " << name << ", how are you?\n"; }
};

class InformalGreetingStrategy : public GreetingStrategy
{
public:
  void greet(const std::string &name) override { std::cout << "Hi " << name << ", what's up?\n"; }
};

class Person
{
  GreetingStrategy *greetingStrategy;

public:
  Person(GreetingStrategy *greeting) : greetingStrategy(greeting) {}
  ~Person() { delete greetingStrategy; }
  void greet(const std::string &name) { greetingStrategy->greet(name); }
};

int main()
{
  Person businessPerson(new FormalGreetingStrategy);
  Person normalPerson(new NormalGreetingStrategy);
  Person friendPerson(new InformalGreetingStrategy);
  Person politicianPerson(new FormalGreetingStrategy);

  businessPerson.greet("Jim");
  normalPerson.greet("Shaun");
  friendPerson.greet("Toby");
  politicianPerson.greet("Freddy");

  return 0;
}