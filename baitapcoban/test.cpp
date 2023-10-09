#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a[10000000];
    int n;
    cin >> n;
    for (int i=0;i<n;i++)
    {
        cin >> a[i];
    }
    for (int i=0;i<n;i++){
    sort(a,a+n);
    cout << a[i]<<" ";
}
}