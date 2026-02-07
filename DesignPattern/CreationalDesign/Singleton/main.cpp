#include <iostream>
#include <string>

class Leader
{
private:
  static Leader *_instance;
  Leader()
  {
    std::cout << "New Leader elected " << std::endl;
  }

public:
  static Leader *getInstance()
  {
    if (!_instance)
    {
      _instance = new Leader;
    }
    return _instance;
  }
  void giveSpeech() { std::cout << "Address the public\n"; }
};

Leader *Leader::_instance = NULL;

int main()
{
  Leader *elected = Leader::getInstance();
  elected->giveSpeech();
  delete elected;
  return 0;
}