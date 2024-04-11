#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s;

void Try(int i) {
    if (i == s.length() - 1) {
        cout << s << endl;
    }
    for (int j = i; j < s.length(); j++) {
        swap(s[i], s[j]);
        Try(i + 1);
        swap(s[i], s[j]); // backtrack
    }
}

int main() {
    cin >> s;
    Try(0);
    return 0;
}