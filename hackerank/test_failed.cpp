#include <bits/stdc++.h>
using namespace std;

class Circle
{
public:
  int radius;
};

class Square
{
public:
  int side;
};

class Shapes
{
public:
  set<int> circle_raduis;
  set<int> square_side;

  friend Shapes operator+(const Shapes s1, const Circle c)
  {
    Shapes sh;
    sh.circle_raduis = s1.circle_raduis;
    sh.circle_raduis.insert(c.radius);
    return sh;
  }
  friend Shapes operator+(const Shapes s1, const Square c)
  {
    Shapes sh;
    sh.square_side = s1.square_side;
    sh.square_side.insert(c.side);
    return sh;
  }
};

int main()
{
  Circle c;
  c.radius = 2;
  Square sq;
  sq.side = 4;
  Shapes sh;
  sh.circle_raduis = set<int>{1, 3, 4};
  sh.square_side = set<int>{8, 9};

  Shapes sh1 = sh + c;
  Shapes sh2 = sh + sq;

  for (const auto s : sh1.circle_raduis)
    cout << s << ", ";
  cout << endl;

  for (const auto s : sh2.square_side)
    cout << s << ", ";
  cout << endl;

  return 0;
}