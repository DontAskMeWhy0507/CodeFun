#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;

  if (a < 12 && b < 12) {
    cout << ((b - a) * 6000) ;
  } else if (a >=12 && b >=12) {
    cout << ((b - a) * 7500);
  } else if (a < 12 && b > 12) {
    cout << ((12 - a) * 6000 + (b - 12) * 7500) ;
  } else if (a)

  return 0;
}