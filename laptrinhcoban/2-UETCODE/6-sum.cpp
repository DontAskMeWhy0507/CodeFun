/*Cho một dãy số A gồm nsố nguyên được sắp xếp theo thứ tự tăng dần (các phần tử thuộc dãy Ađược đánh số từ 1đến n)
và một số nguyên k. Bạn hãy viết chương trình tìm cặp số nguyên i<j
sao cho Ai+Aj=k
.*/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    long long n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++)
        cin >> a[i];

    long long right = n - 1, left = 0;
    while(left < right)
    {
        if(a[left] + a[right] == k)
        {
            while (a[right-1]==a[right]) right --;
            cout << left + 1 << " " << right + 1;
            return 0;
        }
        else if(a[left] + a[right] < k)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    cout << -1;
    return 0;
}