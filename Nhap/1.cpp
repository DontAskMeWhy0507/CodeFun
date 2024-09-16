#include <iostream>
using namespace std;

int uscln(int a, int b)
{
    if(a==b) return a;
    if(a>b) return uscln(a-b,b);
    return uscln(a,b-a);
}

int main()
{
    int a,b;
    cin >> a >> b;
    cout << uscln(a,b);
}