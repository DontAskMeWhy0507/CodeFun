#include <bits/stdc++.h>
using namespace std;

#define int long long

const int maxN=1e3;

int n, m, a[maxN+5];
vector <int> ans;

void input()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        cin >> a[i];
    }
}

void solve()
{
    sort(a+1, a+m+1);
    ans.push_back(n);
    for(int i = m; i >= 1; i--)
    {
        while(n%a[i]==0)
        {
            n/=a[i];
            ans.push_back(n);
        }
    }
    reverse(ans.begin(), ans.end());
    if(ans[0]!=1)
    {
        cout << -1;
        return;
    }
    for(auto i: ans) cout << i << " ";
}

signed main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    input();
    solve();
}
