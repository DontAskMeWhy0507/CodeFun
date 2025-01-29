#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    
    stack<int> st;
    queue<int> q;
    string ans = "-1";
    
    string s;
    getline(cin,s);
    stringstream ss(s);
    while(n--) {
        string bien;
        ss >> bien;
        int a;
        ss >> a;
        if (bien == "push") {
            st.push(a);
            q.push(a);
        } else if (bien == "pop") {
            if (!st.empty()) {
                if (st.top() == a){
                    if (ans == "queue") {
                        cout << -1;
                        return 0;
                    }
                    ans = "stack";
                    st.pop();
                }
                } else if (q.front() == a) {
                    if (ans == "stack") {
                        cout << -1;
                        return 0;
                    }
                    ans = "queue";
                       q.pop();
                }
             
                
      
        }
        
    }
    cout << ans;
}

