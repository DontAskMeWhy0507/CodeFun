#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int d = 256;
const int q = 101;

int rabinKarp(string pat, string txt) {
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; 
    int t = 0; 
    int h = 1;
    int count = 0;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }

            if (j == M)
                count++;
        }

        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return count;
}

int main() {
    int numberOfTestCases;
    cin >> numberOfTestCases;
    while (numberOfTestCases--) {
        string a, b;
        cin >> a >> b;
        cout << rabinKarp(a, b) << endl;
    }     

    return 0;
}
