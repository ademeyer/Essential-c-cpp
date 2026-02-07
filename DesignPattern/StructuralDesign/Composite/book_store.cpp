#include <bits/stdc++.h>

/*
Items for sales:
* Books
* Toys
* Boxes of items (can contain other boxes)
*/

class Product
{
public:
  virtual ~Product() = default;
  virtual double price() const = 0;
};

class Book : public Product
{
  std::string _name;
  double _price;

public:
  Book(const std::string &name, const double &price)
      : _name(), _price(price) {}
  double price() const override { return _price; }
};

class Toy : public Product
{
  std::string _name;
  double _price;

public:
  Toy(const std::string &name, const double &price)
      : _name(), _price(price) {}
  double price() const override { return _price; }
};

class Box : public Product
{
  double _price;
  int _size;
  std::vector<Product *> _boxes;

public:
  Box(const double &price, const int &size)
      : _price(price), _size(size) {}
  void addProduct(Product *product) { _boxes.push_back(product); }
  double price() const override
  {
    double totalPrice = _price;
    for (const auto &b : _boxes)
      totalPrice += b->price();
    return totalPrice;
  }
};

int main()
{
  // Create Books
  Book book1("C++ Essentials", 10);
  Book book2("C++ Design Patterns", 50);

  // Create Toys
  Toy toy1("PS-5", 100);
  Book toy2("X-box", 160);

  Box smallBox(0.5, 1);
  // Add books
  smallBox.addProduct(&book1);
  smallBox.addProduct(&book2);

  Box bigBox(1.2, 5);
  // Add Tous
  bigBox.addProduct(&toy1);
  bigBox.addProduct(&toy2);

  std::cout << "total product price: " << bigBox.price() << std::endl;

  return 0;
}