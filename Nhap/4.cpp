#include <iostream>
using namespace std;
int main()
{
    int n,k;
    cin >> n >>k;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >>a[i];
    }
    int left  = 0; int current = 0; int ans = 99;
    for (int right = 0; right < n; right++)
    {
        current += a[right];
        while(current > k)
        {
            
            current-=a[right] ;
            left++;
        }
        ans = min(ans,right - left);
    }
    cout << ans;
}