#include <fstream>
#include <vector>
using namespace std;
void housesOfHogwarts(const char* path){
  ifstream file(path);
 if (!file.is_open()) {
  cout << "Không thể mở tệp." << endl;
  return;
 }
 // Đọc số lượng phù thủy
 int n;
 file >> n;
 // Đọc tên các phù thủy
 vector<string> tenPhuThuy;
 for (int i = 0; i <= n; i++) {
  string ten;
  getline(file, ten); 

  tenPhuThuy.push_back(ten);
 }
 // In ra màn hình tên các phù thủy
 for (string ten : tenPhuThuy) {
  cout << ten << endl;
 }
 file.close();
}