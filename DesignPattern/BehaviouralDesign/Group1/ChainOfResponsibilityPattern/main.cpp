#include <iostream>
#include <regex>

// Base StringValidator class
class StringValidator
{
public:
  virtual ~StringValidator() {}
  virtual StringValidator *setNext(StringValidator *nextValidator) = 0;
  virtual std::string validate(const std::string &) = 0;
};

// Base BaseValidator class
class BaseValidator : public StringValidator
{
protected:
  StringValidator *next = nullptr;

public:
  virtual ~BaseValidator() { delete next; }
  StringValidator *setNext(StringValidator *nextValidator) override
  {
    next = nextValidator;
    return nextValidator;
  }
  std::string validate(const std::string &test_str) override
  {
    if (this->next)
      return this->next->validate(test_str);

    return "Success!";
  }
};

// Concrete NotEmptyValidator class
class NotEmptyValidator : public BaseValidator
{
public:
  NotEmptyValidator() {}
  std::string validate(const std::string &test_str)
  {
    puts("Checking if empty...");
    if (test_str.empty())
      return "Please Enter a value";

    return BaseValidator::validate(test_str);
  }
};

// Concrete LengthValidator class
class LengthValidator : public BaseValidator
{
  int _minLength;

public:
  LengthValidator(const int &minLength) : _minLength(minLength) {}
  std::string validate(const std::string &test_str)
  {
    puts("Checking string length...");
    if (test_str.size() < _minLength)
      return "Please enter a value longer than " + std::to_string(_minLength);

    return BaseValidator::validate(test_str);
  }
};

// Concrete RegexValidator class
class RegexValidator : public BaseValidator
{
  std::string _patternName;
  std::string _regexString;

public:
  RegexValidator(const std::string &patternName, const std::string &regexString)
      : _patternName(patternName), _regexString(regexString) {}
  std::string validate(const std::string &test_str)
  {
    puts("Checking regex match...");
    if (!std::regex_match(test_str, std::regex(_regexString)))
      return "The value entered does not match the proper format for a " + _patternName;

    return BaseValidator::validate(test_str);
  }
};

bool in_array(const std::string &value, const std::vector<std::string> &array)
{
  return std::find(array.begin(), array.end(), value) != array.end();
}

// Concrete HistoryValidator class
class HistoryValidator : public BaseValidator
{
  std::vector<std::string> _historyItems;

public:
  HistoryValidator(const std::vector<std::string> &historyItems)
      : _historyItems(historyItems) {}
  std::string validate(const std::string &test_str) override
  {
    puts("Checking if string has been used before...");
    if (in_array(test_str, _historyItems))
      return "Please enter a value here that you haven't enetered before";

    return BaseValidator::validate(test_str);
  }
};

int main()
{
  StringValidator *emailValidator = new BaseValidator;
  emailValidator->setNext(new NotEmptyValidator)
      ->setNext(new RegexValidator("email address",
                                   "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));

  std::cout << "Checking Emails ---------\n";
  std::cout << "Input: \n"
            << emailValidator->validate("") << "\n\n";
  std::cout << "Input: shaun\n"
            << emailValidator->validate("shaun") << "\n\n";
  std::cout << "Input: shaun@test.com\n"
            << emailValidator->validate("shaun@test.com") << "\n\n";

  delete emailValidator;
  return 0;
}
