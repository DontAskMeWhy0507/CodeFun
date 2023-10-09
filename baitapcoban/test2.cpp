#include <iostream>

using namespace std;

int main() {
  int n;
  cout << "Nhap n: ";
  cin >> n;

  // Khởi tạo biến max có giá trị là 0
  int max = 0;

  // Dùng vòng lặp while để lấy ra lần lượt các chữ số của số nguyên dương n
  while (n > 0) {
    // Lấy ra chữ số hàng đơn vị của n
    int digit = n % 10;

    // So sánh các chữ số đó với giá trị max
    if (digit > max) {
      // Nếu giá trị max nhỏ hơn thì ta gán cho max giá trị của chữ số đó
      max = digit;
    }

    // Chia n cho 10 để lấy ra chữ số hàng chục
    n /= 10;
  }

  // In ra chữ số lớn nhất của số nguyên dương n
  cout << "Chu so lon nhat cua n la: " << max << endl;

  return 0;
}
