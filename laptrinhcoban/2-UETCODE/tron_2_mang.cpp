#include <iostream>
using namespace std;

int main() {
    int m, n;
    cin >> m;
    int a[m];
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    cin >> n;
    int b[n];
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int i = 0, j = 0;
    while (i < m && j < n) {
        if (a[i] < b[j]) {
            cout << a[i++] << " ";
        } else {
            cout << b[j++] << " ";
        }
    }

    // Print remaining elements
    while (i < m) {
        cout << a[i++] << " ";
    }
    while (j < n) {
        cout << b[j++] << " ";
    }

    return 0;
}