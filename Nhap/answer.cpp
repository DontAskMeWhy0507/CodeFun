#include <bits/stdc++.h>
using namespace std;

void generateExpressions(int n, int m, int a[], string expr, long long sum, long long prev, int start) {
    if (start == n) {
        if (sum == m) {
            cout << expr << endl;
        }
        return;
    }
    generateExpressions(n, m, a, expr + "+" + to_string(a[start]), sum + a[start], a[start], start + 1);
    generateExpressions(n, m, a, expr + "-" + to_string(a[start]), sum - a[start], -a[start], start + 1);
    generateExpressions(n, m, a, expr + "*" + to_string(a[start]), sum - prev + prev * a[start], prev * a[start], start + 1);
}

int main() {
    int n, m; 
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++) 
        cin >> a[i];
    generateExpressions(n, m, a, to_string(a[0]), a[0], a[0], 1);
}