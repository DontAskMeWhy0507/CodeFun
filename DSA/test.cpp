#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
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
        }
        else if(n == 2) {
            prev = ans;
            int k;
            cin >> k;
            ans = ans.substr(0, ans.size() - k);
            st.push(2);
        }
        else if(n == 3) {
            int k;
            cin >> k;
            cout << ans[k - 1] << endl;
        }
        else {
            if(st.top() == 1) {
                ans = prev;
                st.pop();
            }
            else {
                ans = prev;
                st.pop();
            }
        }
    }

    return 0;
}
