#include <iostream>

class Visitor
{
public:
  virtual void handlePerson(const std::string &name, int age) = 0;
  virtual void handleLandmark(const std::string &name, const std::string &cityName) = 0;
  virtual void handleCar(const std::string make, const std::string &model) = 0;
};

class DataBaseVisitor : public Visitor
{
public:
  void handlePerson(const std::string &name, int age) override { std::cout << "Writing person to a database: " << name << ", " << age << "\n"; }
  void handleLandmark(const std::string &name, const std::string &cityName) override { std::cout << "Writing Landmark to a database: " << name << ", " << cityName << "\n"; }
  void handleCar(const std::string make, const std::string &model) override { std::cout << "Writing car to a database: " << make << ", " << model << "\n"; }
};

class TextFileVisitor : public Visitor
{
public:
  void handlePerson(const std::string &name, int age) override { std::cout << "Writing person to a textfile: " << name << ", " << age << "\n"; }
  void handleLandmark(const std::string &name, const std::string &cityName) override { std::cout << "Writing Landmark to a textfile: " << name << ", " << cityName << "\n"; }
  void handleCar(const std::string make, const std::string &model) override { std::cout << "Writing car to a textfile: " << make << ", " << model << "\n"; }
};

class Person
{
  std::string name;
  int age;

public:
  Person(const std::string &name, const int &age) : name(name), age(age) {}
  void accept(Visitor *v) { v->handlePerson(name, age); }
};

class LandMark
{
  std::string name;
  std::string cityName;

public:
  LandMark(const std::string &name, const std::string &cityname) : name(name), cityName(cityname) {}
  void accept(Visitor *v) { v->handleLandmark(name, cityName); }
};

class Car
{
  std::string make;
  std::string model;

public:
  Car(const std::string &make, const std::string &model) : make(make), model(model) {}
  void accept(Visitor *v) { v->handleCar(make, model); }
};

int main()
{
  Person person("John", 40);
  LandMark landmark("Manitoba", "Canada");
  Car car("Audi", "S5 2018");

  DataBaseVisitor *dbv = new DataBaseVisitor;
  TextFileVisitor *tfv = new TextFileVisitor;

  person.accept(dbv);
  landmark.accept(dbv);
  car.accept(dbv);

  person.accept(tfv);
  landmark.accept(tfv);
  car.accept(tfv);

  delete dbv;
  delete tfv;

  return 0;
}