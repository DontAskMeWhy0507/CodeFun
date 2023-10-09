#include <iostream>
using namespace std;
int main ()
{
    int n, a[100];
    bool b = false;
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> a[i];
        if (a[i] == 42)
        {
            b = true;
        }
    }
    if (b)
    {
        cout << "I've found the meaning of life!";
    }else cout <<"It's a joke!";;
}