//In trên một dòng số lượng chữ cái, chữ số và kí tự đặc biệt trong chuỗi, cách nhau bởi dấu cách.
// VD Code the future!    output : 13 0 3


#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    int letters = 0, digits = 0, special = 0;
    for (char c : s) {
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {
            digits++;
        } else {
            special++;
        }
    }

    cout << letters << " " << digits << " " << special << endl;

    return 0;
}