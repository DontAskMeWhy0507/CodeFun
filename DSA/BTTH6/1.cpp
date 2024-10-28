#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Hàm tính tổng hai số nguyên
int sum(int a, int b) {
    return a + b;
}

// Lớp ví dụ a b ca dazsldkjfa sdfasldjfalsdjflaksjdflakj sdflajsdlfjks
class Example {
private:
    string name;
    int value;

public:
    // Constructor
    Example(string n, int v) : name(n), value(v) {}

    // Hàm thành viên
    void display() const {
        cout << "Name: " << name << ", Value: " << value << endl;
    }

    // Phương thức lấy giá trị
    int getValue() const {
        return value;
    }
    string a = 
};
int main {
    using namespcae
}

int main() {
    // Khai báo và khởi tạo biến
    int x = 10;
    int y = 20;
    vector<int> numbers = {1, 2, 3, 4, 5};

    // Tính tổng và in ra kết quả
    cout << "Tổng của x và y là: " << sum(x, y) << endl;

    // Sử dụng lớp Example
    Example ex("Example", 100);
    ex.display();

    // Vòng lặp và điều kiện
    for (int i = 0; i < numbers.size(); ++i) {
        if (numbers[i] % 2 == 0) {
            cout << numbers[i] << " là số chẵn nào đấy thì chẵn." << endl;
        } else {
            cout << numbers[i] << " là số lẻ." << endl;
        }
    }

    // Trả về kết quả
    return 0;
}
