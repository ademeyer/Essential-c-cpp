#include <iostream>
#include <vector>

class Canvas;

class CanvasMomento
{
  friend class Canvas;
  const std::vector<std::string> shapes;

public:
  CanvasMomento(std::vector<std::string> shapes) : shapes(shapes) {}
};

class Canvas
{
  std::vector<std::string> shapes;
  std::vector<CanvasMomento *> oldstates;

public:
  ~Canvas()
  {
    for (auto p : oldstates)
      delete p;
  }
  void addShape(const std::string &newShape)
  {
    oldstates.push_back(new CanvasMomento(shapes));
    shapes.push_back(newShape);
  }
  void undo()
  {
    CanvasMomento *previousState = oldstates.back();
    oldstates.pop_back();
    shapes = previousState->shapes;
    delete previousState;
  }
  void clearAll() { shapes.clear(); }
  std::vector<std::string> getShapes() const { return shapes; }
};

int main()
{
  Canvas *canvas = new Canvas;

  canvas->addShape("rhombus");
  canvas->addShape("triangle");
  canvas->addShape("square");
  canvas->addShape("circle");

  for (const auto &sh : canvas->getShapes())
    std::cout << sh << ", ";
  std::cout << std::endl;

  canvas->undo();

  for (const auto &sh : canvas->getShapes())
    std::cout << sh << ", ";
  std::cout << std::endl;

  canvas->addShape("rhombus");
  canvas->addShape("square");
  canvas->addShape("circle");
  canvas->addShape("triangle");

  canvas->undo();

  for (const auto &sh : canvas->getShapes())
    std::cout << sh << ", ";
  std::cout << std::endl;

  delete canvas;
  return 0;
}