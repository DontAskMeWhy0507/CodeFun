#include <bits/stdc++.h>
using namespace std;
bool nt(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= sqrt(n); ++i)
        if (n % i == 0)
            return false;
    return true;

}
int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
    {
        if(nt(a[i]))
        {
            for (int j = i+1; j < n; ++j)
            {
                if (nt(a[j]))
                    swap(a[i], a[j]);
            }
        }
    }
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
}