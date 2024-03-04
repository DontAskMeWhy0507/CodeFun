#include <iostream>
using namespace std;

bool nguyentocungnhau(int a, int b)
{
    if(a==0 || b==0)
    {
        return false;
    }
    while(a!=b)
    {
        if(a>b)
        {
            a=a-b;
        }
        else
        {
            b=b-a;
        }
    }
    if(a==1)
    {
        return true;
    }
    return false;
    
}

void kq(int n,int a[],int &c, int &d)
{
    
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(nguyentocungnhau(a[i],a[j])==true)
            {
                if(a[i]+a[j]>c+d){
                c=a[i];
                d=a[j];
                }
             
            }
        }
    }
}

int main()
{
    int n;
    cin>>n;
    int a[n];
   
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int c=0,d=0;
   kq(n,a,c,d);
    cout<<c<<" "<<d;
}