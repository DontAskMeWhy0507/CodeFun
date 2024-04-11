#include <iostream>
#include <string>
using namespace std;

int n, m;
int a[100];
int cn, cm;

void print() {
    for (int i = 1; i <= n + m; i++)
        cout << a[i];
    cout << endl;
}

void Try(int i) {
    for (int j = 0; j < 2; j++) {
        if ((j == 0 && cn > 0) || (j == 1 && cm > 0)) {
            a[i] = j;
            if (j == 0) cn--;
            else cm--;
            if (i == n + m) {
                print();
            } else {
                Try(i + 1);
            }
            if (j == 0) cn++;
            else cm++;
        }
    }
}

int main() {
    cin >> n >> m;
    cn = n;
    cm = m;
    Try(1);
    return 0;
}