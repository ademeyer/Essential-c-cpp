#include <istream>

// Base Class Animal
class Animal
{
protected:
  std::string _hairColor;
  int _hairLength, _tail, _weight, _height, _age;
  int _intelligence, _stubborness, _agressiveness;

public:
  virtual Animal *Clone() = 0;
  void setHairLength(const int &length) { _hairLength = length; }
  void setHairColor(const std::string &color) { _hairColor = color; }
  void setTail(const int &length) { _tail = length; }
  void setWeight(const int &kg) { _weight = kg; }
  void setHeight(const int &m) { _height = m; }
  void setAge(const int &age) { _age = age; }
  void setHeight(const int &m) { _height = m; }
};

// Derived Sheep class
class Sheep : public Animal
{
public:
  Sheep()
  {
    _hairLength = 5;
    _stubborness = 3;
    _agressiveness = 2;
    _intelligence = 7;
  }

  Sheep *Clone() { return new Sheep(*this); }
  void sheering() { _hairLength -= 2; }
};

// Derived Cow class
class Cow : public Animal
{
public:
  Cow()
  {
    _stubborness = 6;
    _agressiveness = 5;
    _intelligence = 8;
  }

  Cow *Clone() { return new Cow(*this); }
};

int main()
{
  // Create initial instance of a Sheep
  Sheep *sheep0 = new Sheep;
  sheep0->setHairColor("white");
  sheep0->setTail(5);
  sheep0->setWeight(90);
  sheep0->setHeight(1);
  sheep0->setAge(5);

  // Create initial instance of a Cow
  Cow *cow0 = new Cow;
  cow0->setHairColor("brown");
  cow0->setTail(20);
  cow0->setWeight(790);
  cow0->setHeight(2);
  cow0->setAge(8);

  Animal *farm[3];
  // Use cloning to populate the farm
  farm[0] = sheep0->Clone();
  farm[1] = cow0->Clone();

  // Change a cow property
  farm[1]->setWeight(1000);

  // shear a Sheep and clone it
  sheep0->sheering();
  farm[2] = sheep0->Clone();

  return 0;
}