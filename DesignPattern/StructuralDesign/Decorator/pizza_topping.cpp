#include <bits/stdc++.h>

class Pizza
{
public:
  virtual std::string Description() = 0;
  virtual double price() = 0;
  virtual ~Pizza() = default;
};

class MagaritaPizza : public Pizza
{
public:
  std::string Description() override { return "This is MagaritaPizza"; }
  double price() override { return 1.5; }
};

class PepperoniPizza : public Pizza
{
public:
  std::string Description() override { return "This is PepperoniPizza"; }
  double price() override { return 1.7; }
};

class ChickensusagePizza : public Pizza
{
public:
  std::string Description() override { return "This is ChickensusagePizza"; }
  double price() override { return 2.1; }
};

// Extra topping Features
class WithTomatoSauceTopping : public Pizza
{
public:
  WithTomatoSauceTopping(Pizza &pizza) : m_Pizza(pizza) {}
  std::string Description() override
  {
    return m_Pizza.Description() + " With Tomato Sauce Topping";
  }

  double price() override
  {
    return m_Pizza.price() + 0.12;
  }

protected:
  Pizza &m_Pizza;
};

class WithExtraCheeseTopping : public Pizza
{
public:
  WithExtraCheeseTopping(Pizza &pizza) : m_Pizza(pizza) {}
  std::string Description() override
  {
    return m_Pizza.Description() + " With Extra Cheese Topping";
  }

  double price() override
  {
    return m_Pizza.price() + 0.23;
  }

protected:
  Pizza &m_Pizza;
};

int main()
{
  std::vector<std::shared_ptr<Pizza>> pizza_order = {
      std::make_shared<MagaritaPizza>(),
      std::make_shared<PepperoniPizza>(),
      std::make_shared<ChickensusagePizza>()};

  // price description and price
  for (const auto &pizz : pizza_order)
  {
    std::cout << "Decription: " << pizz->Description() << std::endl;
    std::cout << "Price: " << pizz->price() << std::endl;
  }

  // price description and price with extra topping
  for (const auto &pizz : pizza_order)
  {
    auto p = pizz.get();
    WithTomatoSauceTopping withextra(*p);
    std::cout << "Decription: "
              << withextra.Description() << std::endl;
    std::cout << "Price: " << withextra.price() << std::endl;
  }

  for (const auto &pizz : pizza_order)
  {
    auto p = pizz.get();
    WithExtraCheeseTopping withextra(*p);
    std::cout << "Decription: "
              << withextra.Description() << std::endl;
    std::cout << "Price: " << withextra.price() << std::endl;
  }

  return 0;
}