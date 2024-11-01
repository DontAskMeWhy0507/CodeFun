#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <set>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    set<int> s;
    int q; cin >> q;
    while(q--) {
        int op; cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            s.insert(x);
        }
        else if (op == 2) {
            int x;
            cin >> x;
            s.erase(x);
        }
        else {
            cout << *s.begin() << endl;
        }
    }
}
