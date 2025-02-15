#include <iostream>
#include <vector>
using namespace std;
int main() {
    // Array 2D.
    int n,m;
    cin >> n >> m;
    int a[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    // Vector 2D.
    vector<vector<int>> b(n, vector<int>(m)); // b[n][m]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
        }
    }

    // Array 2D string.
    string s[n][m];

    // Vector 2D string.
    vector<vector<string>> t(n, vector<string>(m)); // t[n][m]
}