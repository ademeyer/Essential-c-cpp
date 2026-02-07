#include <iostream>

enum class CoffeeType
{
  ESPRESSO,
  CAPPUCCINO,
};

// Product from which the concrete products will inherit from
class Coffee
{
protected:
  std::string _type;

public:
  Coffee(const std::string &type) : _type(type) {}
  std::string getType() const { return _type; }
};

// Concrete Class: Espresso
class Espresso : public Coffee
{
public:
  Espresso() : Coffee("Espresso")
  {
    std::cout << "\nMaking a cup of espresso\n";
    std::cout << "Grind and brew one scoop of espresso bean.\n";
  }
};

// Concrete Class: Cappuccino
class Cappuccino : public Coffee
{
public:
  Cappuccino() : Coffee("Cappuccino")
  {
    std::cout << "\nMaking a cup of cappuccino\n";
    std::cout << "Grind and brew one scoop of espresso bean.\n";
    std::cout << "Heat and foam milk.\n";
  }
};

class CofferMakerFactory
{
private:
  Coffee *_coffee;

public:
  Coffee *GetCoffee()
  {
    int choice = -1;

    std::cout << "Select tyoe of coffee to make: \n1: Espresso\n2:Cappuccino\nSelection: ";
    std::cin >> choice;
    std::cout << std::endl;

    switch (choice)
    {
    case 1:
      return new Espresso();
    case 2:
      return new Cappuccino();
    default:
      return NULL;
    }
  }
};

int main()
{
  CofferMakerFactory coffeeMachine;
  auto coffee = coffeeMachine.GetCoffee();
  if (coffee)
  {
    std::cout << "You got: " << coffee->getType() << std::endl;
    delete coffee;
  }
  else
    std::cout << "Invalid Selection\n";

  return 0;
}