#include <bits/stdc++.h>
using namespace std;
void reverse(char*p)
{
    int n=strlen(p);
    for (int i=0;i<n;i++)
    {
        char tmp=p[i];
        p[i]=p[n-i-1];
        p[n-i-1]=tmp;
    }
    cout<<p<<endl;
}
int main()
{
    char s[]="Trung dep.";
    reverse(s);
}