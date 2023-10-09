#include <iostream>
#include <string>

using namespace std;

int main() {
  string S = "Hello, world!";
  int i = 5;
  int j = 6;

  // Đổi chỗ hai ký tự
  S.swap(i, j);

  // In ra xâu S sau khi đổi chỗ
  cout << S << endl;

  return 0;
}
