#include <iostream>

class Mediator
{
public:
  virtual void mediate(const std::string &event) = 0;
};

class InterfaceElement
{
protected:
  Mediator *_mediator;
  std::string _name;
  bool _isVisible;

public:
  InterfaceElement(const std::string &name, const bool &isVisible, Mediator *mediator)
      : _name(name), _isVisible(isVisible), _mediator(mediator) {}
  void setVisibility(const bool &isVisible) { this->_isVisible = isVisible; }
  std::string getDescription()
  {
    return (_name + (_isVisible ? " is visible" : " is NOT visible"));
  }
};

class ButtonElement : public InterfaceElement
{
public:
  ButtonElement(const std::string &name, const bool &isVisible, Mediator *mediator)
      : InterfaceElement(name, isVisible, mediator) {}
  virtual ~ButtonElement() {}
  virtual void click() { _mediator->mediate(_name + " clicked"); }
};

class TextBox : public InterfaceElement
{
  std::string _textValue;

public:
  TextBox(const std::string &name, const bool &isVisible, Mediator *mediator)
      : InterfaceElement(name, isVisible, mediator) {}
  virtual ~TextBox() {}
  virtual void changeText(const std::string &newValue)
  {
    _textValue = newValue;
    _mediator->mediate(_name + (newValue.empty() ? " empty" : " not empty"));
  }
};

class CheckBox : public InterfaceElement
{
  bool _isChecked;

public:
  CheckBox(const std::string &name, const bool &isVisible, Mediator *mediator)
      : InterfaceElement(name, isVisible, mediator) {}
  virtual ~CheckBox() {}
  virtual void setIsChecked(const bool &isChecked)
  {
    _isChecked = isChecked;
    _mediator->mediate(_name + (isChecked ? " checked" : " unchecked"));
  }
};

// class SubmitButton : public ButtonElement
// {
// public:
//   SubmitButton() : ButtonElement("Submit Button", false) {}
//   void click() override { std::cout << "Submitted!\n"; }
// };

// class NameTextBox : public TextBox
// {
//   SubmitButton *_submitButton;

// public:
//   NameTextBox(SubmitButton *submitButton)
//       : TextBox("Name textbox", false), _submitButton(submitButton) {}
//   void changeText(const std::string &newValue) override
//   {
//     _submitButton->setVisibility(newValue.empty() ? false : true);
//     TextBox::changeText(newValue);
//   }
// };

// class SpousesNameTextBox : public TextBox
// {
// public:
//   SpousesNameTextBox() : TextBox("Spouse's name textbox", false) {}
// };

// class IsMarriedCheckBox : public CheckBox
// {
//   SpousesNameTextBox *_spouseNameTextBox;

// public:
//   IsMarriedCheckBox(SpousesNameTextBox *spouseNameTextBox)
//       : CheckBox("Is married checkbox", true), _spouseNameTextBox(spouseNameTextBox) {}
//   void setIsChecked(const bool &isChecked) override
//   {
//     _spouseNameTextBox->setVisibility(isChecked);
//     CheckBox::setIsChecked(isChecked);
//   }
// };

class UserInterface : public Mediator
{
  TextBox *_nameTextBox;
  CheckBox *_isMarriedCheckBox;
  TextBox *_spousesNameTextBox;
  ButtonElement *_submitButton;

public:
  UserInterface()
  {
    _nameTextBox = new TextBox("Name textbox", true, this);
    _isMarriedCheckBox = new CheckBox("Is married checkbox", true, this);
    _spousesNameTextBox = new TextBox("Spouse's name textbox", false, this);
    _submitButton = new ButtonElement("Submit button", false, this);
  }
  ~UserInterface()
  {
    delete _nameTextBox;
    delete _isMarriedCheckBox;
    delete _spousesNameTextBox;
    delete _submitButton;
  }
  void mediate(const std::string &event) override
  {
    std::cout << "Mediating event: " << event << "...\n";

    if (event == "Name textbox is empty")
      _submitButton->setVisibility(false);
    else if (event == "Name textbox is not empty")
      _submitButton->setVisibility(true);
    else if (event == "Is married checkbox checked")
      _spousesNameTextBox->setVisibility(true);
    else if (event == "Is married checkbox is unchecked")
      _spousesNameTextBox->setVisibility(false);
    else if (event == "Submit button clicked")
      std::cout << "Submitted!\n";
    else
      std::cout << "Unrecognized event: " << event << "\n";
  }
  TextBox *getNameTextBox() { return _nameTextBox; }
  CheckBox *getIsMarriedCheckBox() { return _isMarriedCheckBox; }
  TextBox *getSpousesNameTextBox() { return _spousesNameTextBox; }
  ButtonElement *getSubmitButton() { return _submitButton; }
};

int main()
{
  UserInterface *ui = new UserInterface;

  InterfaceElement *elements[] =
      {
          ui->getNameTextBox(),
          ui->getIsMarriedCheckBox(),
          ui->getSpousesNameTextBox(),
          ui->getSubmitButton()};

  for (const auto element : elements)
    std::cout << element->getDescription() << std::endl;

  ui->getIsMarriedCheckBox()->setIsChecked(true);

  for (const auto element : elements)
    std::cout << element->getDescription() << std::endl;

  delete ui;

  return 0;
}