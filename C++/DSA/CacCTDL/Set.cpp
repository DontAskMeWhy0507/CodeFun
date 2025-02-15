#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

int main() {

    // Ham set khong sap xep
    unordered_set<int> s;
    // Them phan tu vao set do phuc tap la O(1)
    s.insert(1);    
    s.insert(3);
    s.insert(2);
    // Tim phan tu trong set do phuc tap la O(1)
    if (s.find(2) != s.end()) {
        cout << "Found" << endl;
    }
    // Xoa phan tu trong set do phuc tap la O(1)
    s.erase(2);


    // Ham set sap xep
    set<int> s1;
    // Them phan tu vao set do phuc tap la O(log(n))
    s1.insert(1);
    s1.insert(3);
    s1.insert(2);
    // Tim phan tu trong set do phuc tap la O(log(n))
    if (s1.find(2) != s1.end()) {
        cout << "Found" << endl;
    }
    // Xoa phan tu trong set do phuc tap la O(log(n))
    s1.erase(2);


    // map khong sap xep
    unordered_map<int, int> m;
    // Them phan tu vao map do phuc tap la O(1)
    m[1] = 2;
    m[3] = 4;
    m[2] = 3;
    // Tim phan tu trong map do phuc tap la O(1)
    if (m.find(2) != m.end()) {
        cout << "Found" << endl;
    }
    // Xoa phan tu trong map do phuc tap la O(1)
    m.erase(2);

    // Map sap xep
    map<int, int> m1;
    // Them phan tu vao map do phuc tap la O(log(n))
    m1[1] = 2;
    m1[3] = 4;
    m1[2] = 3;
    // Tim phan tu trong map do phuc tap la O(log(n))
    if (m1.find(2) != m1.end()) {
        cout << "Found" << endl;
    }
    // Xoa phan tu trong map do phuc tap la O(log(n))
    m1.erase(2);

    //Stack
    stack<int> st;
    // Them phan tu vao stack do phuc tap la O(1)
    st.push(1);
    st.push(2);
    // Lay phan tu tren cung cua stack do phuc tap la O(1)
    cout << st.top() << endl;
    // Xoa phan tu tren cung cua stack do phuc tap la O(1)
    st.pop();


    //Queue
    queue<int> q;
    // Them phan tu vao queue do phuc tap la O(1)
    q.push(1);
    q.push(2);
    // Lay phan tu dau tien cua queue do phuc tap la O(1)
    cout << q.front() << endl;
    // Xoa phan tu dau tien cua queue do phuc tap la O(1)
    q.pop();
    //  Lay phan tu cuoi cung cua queue do phuc tap la O(1)
    cout << q.back() << endl;

    
}