#include <iostream>
using namespace std;
int xoaso(int a[],int vitri,int n){
    for(int i=vitri;i<n;i++)
    {
        a[i]=a[i+1];
    }
    return n-1;
}
int main(){
    int n;cin>>n;
    int a[n],MIN=100; 
    for(int i=0;i<n;i++)
    {
       cin>>a[i]; 
    }
    for(int i=0;i<n-5;i++)
    {
     for(int j=1;j<n-2;i++)
     {
         MIN=min(MIN,a[j]);
     }
     int vitri=10;
     for(int j=i+1;j<n-2;j++)
     {
         if(a[j]==MIN)
         {
             vitri=j;    
             n=xoaso(a,vitri,n);
         }
     }
     
    }
    for (int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
}