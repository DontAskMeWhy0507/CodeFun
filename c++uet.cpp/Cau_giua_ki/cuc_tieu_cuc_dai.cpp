#include <iostream>
using namespace std;

int xoaso(int a[], int n, int x) {
    for (int i = x; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    return n - 1;
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool found;
    do {
        found = false;
        for (int i = 1; i < n - 1; i++) {
            if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
                n = xoaso(a, n, i);
                found = true;
                break;
            }
        }
    } while (found);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    return 0;
}