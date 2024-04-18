#include <iostream>
using namespace std;

long long count(string s)
{
    long long  dem = 0;
    long long len = s.length();
    for (long long i  = 0; i< len;i++)
    {
        long long tmp = s[i]-'0';
        dem+=tmp;
    }
    return dem;
}

int main()
{
    string s;
    cin>>s;
    cout <<count(s);
}