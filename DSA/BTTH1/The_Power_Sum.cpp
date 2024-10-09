#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'powerSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER X
 *  2. INTEGER N
 */

int power(int n, int k) {
    int res = 1;
    for (int i = 1; i <= k; i++) {
        res *= n;
        if (res > 1e9) return 1e9;
    }
    return res;
}

int powerSum(int X, int N) {
    int f[10001]; // Increase the size of the array to handle larger values of X
    memset(f, 0, sizeof(f));
    f[0] = 1; // Initialize f[0] to 1

    for (int i = 1; i <= X; i++) {
        int p = power(i, N);
        if (p > X) break; // If power exceeds X, break the loop
        for (int j = X; j >= p; j--) {
            f[j] += f[j - p];
        }
    }
    return f[X];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string X_temp;
    getline(cin, X_temp);

    int X = stoi(ltrim(rtrim(X_temp)));

    string N_temp;
    getline(cin, N_temp);

    int N = stoi(ltrim(rtrim(N_temp)));

    int result = powerSum(X, N);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
