#include <iostream>

class State
{
protected:
  State *nextState;

public:
  virtual std::string getDescription() = 0;
  virtual State *getNextState() { return nextState; };
};

class PurchaseState : public State
{
public:
  PurchaseState(State *next) { nextState = next; }
  std::string getDescription() override { return "Current State: PURCHASED - Will be shipping soon\n"; }
};

class InTransitState : public State
{
public:
  InTransitState(State *next) { nextState = next; }
  std::string getDescription() override { return "Current State: INTANSITSTATE - Will be delivered soon\n"; }
};

class DeliveredState : public State
{
public:
  DeliveredState(State *next) { nextState = next; }
  std::string getDescription() override { return "Current State: DELIVEREDSTATE - See you shopping soon\n"; }
};

class Purchase
{
  std::string productName;
  State *currentState;

public:
  Purchase(const std::string &productname, State *initial_state)
      : productName(productname), currentState(initial_state) {}
  std::string getDescription()
  {
    if (currentState)
      return currentState->getDescription();
    return "Purchase is completed!\n";
  }
  void gotoNextState()
  {
    if (currentState->getNextState())
      currentState = currentState->getNextState();
    else
      std::cout << "No more state to process!\n";
  }
};

int main()
{
  DeliveredState *deliveredState = new DeliveredState(nullptr);
  InTransitState *intransitState = new InTransitState(deliveredState);
  PurchaseState *purchaseState = new PurchaseState(intransitState);

  Purchase *purchase = new Purchase("Milk", purchaseState);

  std::cout << purchase->getDescription() << "\n";

  purchase->gotoNextState();
  std::cout << purchase->getDescription() << "\n";

  purchase->gotoNextState();
  std::cout << purchase->getDescription() << "\n";

  delete deliveredState;
  delete intransitState;
  delete purchaseState;
  delete purchase;

  return 0;
}