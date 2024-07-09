#include <bits/stdc++.h>
using namespace std;
int n; int a[1000];



void print()
{
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << ' ';
    }
    cout << endl;
}
void Try(int k)
{
    for(int j = 0; j <= 1; j++)
    {
        a[k] = j;
        if(k == n)
        {
            print();
        }
        else Try(k+1);
    }
}


int main()
{
    cin >> n;
    Try(1);
}