
#include <iostream>
#include <string>
using namespace std;

void generate(string chars, int length, string &res) {
    if ((int)res.length() == length) {
        cout << res << endl;
        return;
    }
    for (char c : chars) {
        res = res + c;
        generate(chars, length, res);
        res.erase(res.length()-1);
    }
}

int main() {
    string chars;
    cin >> chars;
    string res("");
    for (int len = 1; len <= (int)chars.length(); ++len) {
        generate(chars, len, res);
        res = "";
    }
    return 0;
}
