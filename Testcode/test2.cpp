#include <iostream>

using namespace std;

int main() {
  // Nhập kích thước ma trận
  int m, n;
  cout << "Nhập kích thước ma trận m x n: ";
  cin >> m >> n;

  // Khởi tạo ma trận
  int matrix[m][n];

  // Nhập vào ma trận
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << "Nhập phần tử thứ " << i + 1 << ", " << j + 1 << ": ";
      cin >> matrix[i][j];
    }
  }

  // In ra phần tử ở vị trí 3x2
  int row = 3;
  int col = 2;
  cout << "Phần tử ở vị trí " << row << "x" << col << " là: " << matrix[row][col] << endl;
//trung dep trai qua vcl
  return 0;
}
