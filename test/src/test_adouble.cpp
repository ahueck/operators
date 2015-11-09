#include "adouble.h"

int main() {
  const adouble pi = 3.14;
  using namespace std;
  adouble a = 10.0;
  adouble b(10.0);
  adouble c = a;

  cout << (a == b) << " - true" << endl;
  cout << (a == c) << " - true" << endl;
  cout << (a != c) << " - false" << endl;
  cout << round(a + 0.5) << " - 11" << endl;
  cout << round(a + 0.4) << " - 10" << endl;
  cout << pow(a, 2.0) << " - 100" << endl;
  cout << max(a, 2.0) << " - 10" << endl;
  cout << min(a, 2.0) << " - 2" << endl;
  cout << (a*b*c) << " - 1000" << endl;
  cout << sin(a*9*pi / 180.0) << " - 1" << endl;
  cout << round(cos(a*9*pi / 180.0)) << " - 0" << endl;

  return 0;
}