#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[n];;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a,a+n);
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        int tmp = 1;
       for (int j = i+1; j < n; j++)
       {
           if (a[j] - a[i] <= 1)
           {
               tmp++;
           }
       }
       ans  = max(ans,tmp);
    }
    cout << ans;
}