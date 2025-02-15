/*
Cho một mảng các số nguyên dương nums
 và một số nguyên dương target
, hãy trả về độ dài  nhỏ nhất của một mảng con có tổng lớn hơn hoặc bằng target
. Nếu không có mảng con như vậy, hãy trả về 0.
*/

#include <iostream>
using namespace std;
int main()
{
    int n,target;
    cin >> n >>target;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >>a[i];
    }
      int left = 0, right = 0;
    int current = 0;
    int ans = 99999;
    while (right < n) {
        current += a[right++];
        while (current >= target) {
            ans = min(ans, right - left);
            current -= a[left++];
        }
    }
    if(ans == 99999) cout <<0;
    else cout << ans;
}