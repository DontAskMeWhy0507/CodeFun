#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class Queue {
    stack<int> st1, st2;

    public:
    void enqueue(int x) {
        st1.push(x);
    }

    void dequeue() {
        if (st2.empty()) {
            while (!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        if (!st2.empty()) {
            st2.pop();
        }
    }

    void printFront() {
        if (st2.empty()) {
            while (!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        if (!st2.empty()) {
            cout << st2.top() << endl;
        }
    }

};

int main() {
    Queue q;
    int n;
    cin >> n;
    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            q.enqueue(x);
        } else if (type == 2) {
            q.dequeue();
        } else {
            q.printFront();
        }
    }
    return 0;
}
