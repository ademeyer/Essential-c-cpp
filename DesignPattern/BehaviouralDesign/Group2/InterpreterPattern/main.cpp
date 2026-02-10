#include <iostream>

class Expression
{
public:
  virtual int evaluate() = 0;
};

// Basic Math OperationExpression
class OperationExpression : public Expression
{

  std::string operatorSymbol;
  Expression *leftHandSide;
  Expression *rightHandSide;

public:
  OperationExpression(const std::string opsymbol, Expression *lhs, Expression *rhs)
      : operatorSymbol(opsymbol), leftHandSide(lhs), rightHandSide(rhs) {}

  int evaluate() override
  {
    if (operatorSymbol == "plus")
      return leftHandSide->evaluate() + rightHandSide->evaluate();
    else if (operatorSymbol == "minus")
      return leftHandSide->evaluate() - rightHandSide->evaluate();
    else
    {
      std::cout << "Unrecognized operator: " << operatorSymbol << std::endl;
      return 0;
    }
  }
};

class NumberExpression : public Expression
{
  std::string numberstr;

public:
  NumberExpression(const std::string &numstr) : numberstr(numstr) {}
  int evaluate() override { return std::stoi(numberstr); }
};

int main()
{
  NumberExpression *five = new NumberExpression("5");
  NumberExpression *seven = new NumberExpression("7");
  OperationExpression *op_sevenplusfive = new OperationExpression("plus", seven, five);

  std::cout << "(7 + 5) = " << op_sevenplusfive->evaluate() << std::endl;

  NumberExpression *thirteen = new NumberExpression("13");
  OperationExpression *complexOp = new OperationExpression("minus", thirteen, op_sevenplusfive);
  std::cout << "13 - (7 + 5) = " << complexOp->evaluate() << std::endl;

  delete five;
  delete seven;
  delete thirteen;
  delete op_sevenplusfive;
  delete complexOp;

  return 0;
}