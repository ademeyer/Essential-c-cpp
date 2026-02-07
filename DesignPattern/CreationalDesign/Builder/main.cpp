#include <iostream>

#pragma region Entrees
// Base Entree class
class Entree
{
protected:
  std::string _entree;

public:
  const std::string getEntree() const { return _entree; }
};

// Derived Burger class
class Burger : public Entree
{
public:
  Burger()
  {
    std::cout << "\n Grill burger patty, add tomatoes and place them in a bun.";
    _entree = " hamburger";
  }
};

// Derived Hotdog class
class Hotdog : public Entree
{
public:
  Hotdog()
  {
    std::cout << "\n Cook sausage and place it in a bun.";
    _entree = " hotdog";
  }
};
#pragma endregion Entrees

#pragma region Sides
// Base Side class
class Side
{
protected:
  std::string _side;

public:
  const std::string getSide() const { return _side; }
};

// Derived Fries class
class Fries : public Side
{
public:
  Fries()
  {
    std::cout << "\n Fry and season potatoes.";
    _side = " fries";
  }
};

// Derived Salad class
class Salad : public Side
{
public:
  Salad()
  {
    std::cout << "\n Toss greens and dressing together. ";
    _side = " salad";
  }
};
#pragma endregion Sides

#pragma region Drinks
// Base Drink class
class Drink
{
protected:
  std::string _drink;

public:
  const std::string getDrink() const { return _drink; }
};

// Derived Soda class
class Soda : public Drink
{
public:
  Soda()
  {
    std::cout << "\n Break ice and pour. ";
    _drink = " soda";
  }
};

// Derived Juice class
class Juice : public Drink
{
public:
  Juice()
  {
    std::cout << "\n Squash fruit and seive. ";
    _drink = " juice";
  }
};
#pragma endregion Drinks

// Complex MealCombo object that contains an Entree. a Side and a Drink object
class MealCombo
{
private:
  Entree *entree;
  Side *side;
  Drink *drink;
  std::string _bag;

public:
  MealCombo(const std::string &type) { _bag = type; }
  void setEntree(Entree *e) { entree = e; }
  void setSide(Side *s) { side = s; }
  void setDrink(Drink *d) { drink = d; }
  std::string openMealBag()
  {
    _bag += entree->getEntree();
    _bag += side->getSide();
    _bag += drink->getDrink();
    return _bag;
  }
};

#pragma region Builders
// Base Builder
class MealBuilder
{
protected:
  MealCombo *_meal;

public:
  virtual void cookEntree() {}
  virtual void cookSide() {}
  virtual void fillDrink() {}

  MealCombo *getMeal() { return _meal; }
};

// Concrete Builder for a Burger Meal which has a burger, fries and a drink
class BurgerMeal : public MealBuilder
{
public:
  BurgerMeal() { _meal = new MealCombo("Burger"); }
  void cookEntree()
  {
    Burger *burger = new Burger;
    _meal->setEntree(burger);
  }
  void cookSide()
  {
    Fries *fries = new Fries;
    _meal->setSide(fries);
  }
  void fillDrink()
  {
    Soda *soda = new Soda;
    _meal->setDrink(soda);
  }
};

// Concrete Builder for a Hotdog Meal which has a hotdog, salad and a juice drink
class HotdogMeal : public MealBuilder
{
public:
  HotdogMeal() { _meal = new MealCombo("Hotdog"); }

  void cookEntree()
  {
    Hotdog *hotdog = new Hotdog;
    _meal->setEntree(hotdog);
  }
  void cookSide()
  {
    Salad *caesar = new Salad;
    _meal->setSide(caesar);
  }
  void fillDrink()
  {
    Juice *juice = new Juice;
    _meal->setDrink(juice);
  }
};

#pragma endregion Builders

int main()
{
  int choice = -1;
  MealBuilder *cook = new MealBuilder;
  MealCombo *meal;

  // Prompt user for their meal choice
  std::cout << "Select a meal: \n1: Hamburger Meal\n2:Hotdog Meal\nSelection: ";
  std::cin >> choice;
  std::cout << std::endl;

  // Instantiate the appropriate builder based on user input
  switch (choice)
  {
  case 1:
    cook = new BurgerMeal;
    break;
  case 2:
    cook = new HotdogMeal;
    break;
  default:
    std::cout << "Invalid selection\n";
    cook = NULL;
    break;
  }

  std::cout << "Making selected meal" << std::endl;

  // Build the complex object
  cook->cookEntree();
  cook->cookSide();
  cook->fillDrink();
  meal = cook->getMeal();

  std::cout << meal->openMealBag() << std::endl;

  delete cook;
  delete meal;

  return 0;
}