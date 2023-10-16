#include <iostream>

using namespace std;

bool isGreaterThanOne(int n) {
  if(n<10)return false;
  return n > 1;
}

int main() {
  int n ;
cin>>n;
  bool isGreater = isGreaterThanOne(n);

  cout << "isGreater: " << isGreater << endl;

  return 0;
}
