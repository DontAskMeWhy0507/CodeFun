// #include <bits/stdc++.h>
// using namespace std;

// #define ll long long
// #define ld long double
// #define int long long  

// int f[1001];

// int pow(int n,int k)
// {
//     int res=1;
//     for (int i=1; i<=k; i++)
//     {
//         res*=n;
//         if (res>1e9) return 1e9;
//         // 1e9 ở đây tương ứng với 10^9
//     }
//     return res;
// }

// int32_t main()
// {
//     int n,k;
//     cin >> n >> k;
//     memset(f, 0, sizeof(f));    // Khởi tạo mảng f toàn bộ bằng 0
//     f[1]=1;
//     f[0]=1;
//     for (int i=2; i<=n; i++)
//         for (int j=n; j>=pow(i,k); j--) 
//             f[j]+=f[j-pow(i,k)];

//     cout << f[n];
// }


#include <bits/stdc++.h>
using namespace std;
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
int powerSum(int X, int N, int lower = 1)
{
    if(pow(lower, N) > X) return 0;
    if(pow(lower, N) == X) return 1;
    int total_way = 0;
    for (int i = lower; pow(i, N) <= X; i++)
    {
        if(pow(i, N) == X) total_way++;
        total_way += powerSum(X - pow(i, N), N, i + 1);
    }
    return total_way;
}