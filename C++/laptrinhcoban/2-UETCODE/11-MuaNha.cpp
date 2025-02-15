/*
    Giá của tòa nhà lúc bán không đươc cao hơn lúc mua ( tức là Bình luôn thua lỗ khi bán nhà).
    Tòa nhà không được bán cùng năm với năm mua tòa nhà này.
*/
  

#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

bool check (pair<long long ,long long > a, pair<long long ,long long > b)
{
    return a.first < b.first;
}

int main()
{
    long long n;
    cin >> n;
    pair<long long , long long > a[n];
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a, a + n,check);
   
    long long Min = INT_MAX;
    for (long long i = 0; i < n -1; i++)
    {
      if(a[i+1].second < a[i].second ) Min = min(Min, a[i + 1].first - a[i].first);
    }
    cout << Min;
}