#include <bits/stdc++.h>

using namespace std;

int mark[26];

void generate(string str, string current, int length) {
    //if(mark[])
    if ((int)current.length() == length) {
        cout << current << endl;
        return;
    }
    for (char c : str) {
        if(mark[c-97] == 1) continue;

        mark[c - 97] = 1;
        generate(str, current + c, length);
        mark[c-97] = 0;
    }
}

int main() {
    string str;
    cin >> str;
    int len = str.length();

    vector <char> vt;
    for(auto ch: str)
        vt.push_back(ch);
    sort(vt.begin(), vt.end());

    for (auto i= 0; i < (int) vt.size(); ++i)
        str[i] = vt[i];

    generate(str, "", len);

    return 0;
}
