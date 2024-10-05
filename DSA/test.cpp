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

int power(int n,int k)
{
    int res=1;
    for (int i=1; i<=k; i++)
    {
        res*=n;
        if (res>1e9) return 1e9;
        
    }
    return res;
}

int powerSum(int X, int N) {
    int f[1001];
    memset(f,0,sizeof(f));
    f[1] = 1;
    f[0] = 1;
    for(int i = 2; i <= X; i++)
    {
        for(int j = X; j >= power(i,N); j--)
        {
            f[j] += f[j - power(i,N)];
        }
    }
    return f[X];
}


