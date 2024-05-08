#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define fi first
#define se second
#define int long long

int f[1001];

int pow(int n,int k)
{
    int res=1;
    for (int i=1; i<=k; i++)
    {
        res*=n;
        if (res>1e9) return 1e9;
        // 1e9 ở đây tương ứng với 10^9
    }
    return res;
}

int32_t main()
{
    int n,k;
    cin >> n >> k;
    memset(f, 0, sizeof(f));
    f[1]=1;
    f[0]=1;
    for (int i=2; i<=n; i++)
        for (int j=n; j>=pow(i,k); j--) f[j]+=f[j-pow(i,k)];
    cout << f[n];
}
