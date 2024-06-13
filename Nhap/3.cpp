#include <bits/stdc++.h>
using namespace std;
long long  main()
{
    long long  n;
    cin >> n; 
    long long  a[n];
    for(long long  i = 0; i < n; ++i) cin >> a[i];
    long long  ans = 999999999;
    for(long long  i = 0; i < n; i++)
    {
        for(long long  j = i + 1; j < n; j++)
        {
            if(a[i] > a[j]) ans = min(ans, a[i] - a[j]);
        }
    }
    cout << ans;
}