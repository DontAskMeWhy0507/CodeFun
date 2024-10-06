#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    int Q;
    cin >> Q;
    string ans = "";
    stack <string> prev;
    prev.push(ans);
    stack <int> st;
    while (Q--) {
        int n;
        cin >> n;
        if(n == 1) {
            string s;
            cin >> s;
            ans += s;
            st.push(1);
            prev.push(ans);
        }
        else if(n == 2) {
            int k;
            cin >> k;
            ans = ans.substr(0, ans.size() - k);
            st.push(2);
            prev.push(ans);
        }
        else if(n == 3) {
            int k;
            cin >> k;
            cout << ans[k - 1] << endl;
        }
        else {
            prev.pop();
            ans = prev.top();
        }
    }

    return 0;
}
