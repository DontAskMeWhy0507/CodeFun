#include <iostream>
using namespace std;
int main(){
    int n,a[100];
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int vitri; cin>>vitri;
    for(int i=0;i<n;i++){
        if(a[i]<vitri&&a[i+1]>vitri){
            int mang=i+1;
           for (int j=n;j>mang;j--){
                     a[j]=a[j-1];}
            a[mang]=vitri;
            }
        else if(a[i]>vitri&&a[i+1]<vitri){
            int mang=i+1;
           for (int j=n;j>mang;j--){
                     a[j]=a[j-1];}
            a[mang]=vitri;
            }
        }
        for(int i=0;i<=n;i++){
        cout<<a[i]<<" ";
    }
    }
   
