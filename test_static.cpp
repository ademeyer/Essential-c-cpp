#include <bits/stdc++.h>
using namespace std;

class Test
{
  static int count;
  int cnt;
  public:
    Test() { ++count; cnt = 200; }
    ~Test(){}
    int get_count() const { return count; }
    static int get_non_static() { return count; }
    
};

int Test::count = 0;

int main()
{
  Test t1;
  int r = t1.get_count();
  int nr = Test::get_non_static();

  cout << "r = " << r << "\nnr = " << nr << endl;
  return 0;
}
