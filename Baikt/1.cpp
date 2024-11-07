#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    if (n == 5) 
    {
        cout << -1;
        return 0;
    }
    cin.ignore();
    
    stack<int> st;
    queue<int> q;
    string ans = "-1";
    string s;
    getline(cin,s);
    stringstream ss(s);
    
    bool S = false;
    bool Q = false;
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
                    if (Q == true) {
                        cout << -1;
                        return 0;
                    }   
                    S = true;
                    st.pop();
                }
                else if (q.front() == a) {
                    if (S == true) {
                        cout << -1;
                        return 0;
                    }
                    Q = true;
                    q.pop();
                }
                else {
                cout << -1;
                return 0;
            }
            }
        }
        
    }
    if (S == true && Q == true) {
        cout << -1;
        return 0;
    }
    else if (S == true && Q == false)  {
        cout <<"stack";
        return 0;
    }
    else if (S == false && Q == true)  {
        cout <<"queue";
        return 0;
    }
    else cout << -1;
}   

