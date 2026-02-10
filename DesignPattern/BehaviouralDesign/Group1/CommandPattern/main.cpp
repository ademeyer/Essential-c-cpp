#include <iostream>
#include <vector>

class Canvas
{
  std::vector<std::string> shapes;

public:
  void addShape(const std::string &newShape) { shapes.push_back(newShape); }
  void clearAll() { shapes.clear(); }
  std::vector<std::string> getShapes() const { return shapes; }
};

class Command
{
public:
  virtual ~Command() {}
  virtual void execute() = 0;
};

class Button
{
  Command *command;

public:
  Button(Command *cmd) : command(cmd) {}
  void click() { command->execute(); }
};

class AddShapeCommand : public Command
{
  std::string shapeName;
  Canvas *canvas;

public:
  AddShapeCommand(const std::string &shapeName, Canvas *canvas)
      : shapeName(shapeName), canvas(canvas) {}
  void execute() { canvas->addShape(shapeName); }
};

class ClearCommand : public Command
{
  Canvas *canvas;

public:
  ClearCommand(Canvas *canvas) : canvas(canvas) {}
  void execute() { canvas->clearAll(); }
};

std::string vectorToString(const std::vector<std::string> &val)
{
  std::string result = "\n";
  for (const auto &str : val)
  {
    result += str;
    result += "\n";
  }
  return result;
}

int main()
{
  Canvas *canvas = new Canvas;
  // create triangle
  Button *addTriangleButton = new Button(new AddShapeCommand("triangle", canvas));
  // create a square
  Button *addSquareButton = new Button(new AddShapeCommand("square", canvas));
  // create a clear button
  Button *clearButton = new Button(new ClearCommand(canvas));

  // Perform button operation
  addTriangleButton->click();
  std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
  addSquareButton->click();
  addSquareButton->click();
  addTriangleButton->click();
  std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
  clearButton->click();
  std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";

  delete canvas;
  return 0;
}