#include <iostream>
using namespace std;
int xoaso(int a[],int n,int x){
    for(int i=x;i<(n);i++){
        a[i-1]=a[i];
    }
    return n-1;
}

int main(){
    int n,a[100],x;
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
     cin>>x;
    n=xoaso(a,n,x);
    for (int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
   
    
}