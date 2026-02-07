#include <iostream>

class Door
{
public:
  virtual ~Door() {}
  virtual void Open() = 0;
};

class GasCarDoor : public Door
{
public:
  GasCarDoor() { std::cout << "Making a door for a gas car.\n"; }
  void Open() override { std::cout << "click\n"; }
};

class ElectricCarDoor : public Door
{
public:
  ElectricCarDoor() { std::cout << "Making a door for a electric car.\n"; }
  void Open() override { std::cout << "sssshhhhh\n"; }
};

// Engine objects
class Engine
{
protected:
  std::string _sound;

public:
  Engine(const std::string &sound) : _sound(sound) {}
  virtual ~Engine() {}
  virtual void Run() = 0;
};

class GasEngine : public Engine
{
public:
  GasEngine() : Engine("vroom") { std::cout << "Making a gas Engine.\n"; }
  void Run() override { std::cout << "Gas Engine make " << _sound << " sound\n"; }
};

class ElectricEngine : public Engine
{
public:
  ElectricEngine() : Engine("SHHHHHH") { std::cout << "Making a electric Engine.\n"; }
  void Run() override { std::cout << "Electric Engine make " << _sound << " sound\n"; }
};

// Factories
class CarFactory
{
public:
  virtual ~CarFactory() {}
  virtual Door *BuildDoor() = 0;
  virtual Engine *BuildEngine() = 0;
};

class GasCarFactory : public CarFactory
{
public:
  Door *BuildDoor() { return new GasCarDoor(); };
  Engine *BuildEngine() { return new GasEngine(); };
};

class ElectricCarFactory : public CarFactory
{
public:
  Door *BuildDoor() { return new ElectricCarDoor(); };
  Engine *BuildEngine() { return new ElectricEngine(); };
};

int main()
{
  CarFactory *carPlant = nullptr;
  int choice = -1;
  std::cout << "Select a car type: \n1: Gasoline\n2: Electric\nSelection: ";
  std::cin >> choice;
  std::cout << std::endl;

  switch (choice)
  {
  case 1:
    carPlant = new GasCarFactory;
    break;
  case 2:
    carPlant = new ElectricCarFactory;
    break;
  default:
    std::cout << "Invalid Selection\n";
    break;
  }

  if (carPlant)
  {
    Door *myDoor = carPlant->BuildDoor();
    Engine *myEngine = carPlant->BuildEngine();

    myDoor->Open();
    myEngine->Run();

    delete myDoor;
    delete myEngine;
    delete carPlant;
  }

  return 0;
}