#include <iostream>
using namespace std;
int xoaso(int a[],int n,int x){
    for(int i=x;i<(n-1);i++){
        a[i]=a[i+1];
    }
    return n-1;
}
int main(){
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;++i){
        cin>>a[i];
    }
    
    int vitri=0;

    for(int i=0;i<n+2;i++){
        int nhonhat=100;
        for(int j=1;j<n-1;++j){
           nhonhat=min(nhonhat,a[j]);
        }
        for(int j=1;j<n-1;++j){
            if(a[j]==nhonhat) {vitri=j; cout<<a[j]<<" "<<endl;}
        }
        cout<<vitri<<" "<<n<<endl;
        n=xoaso(a,n,vitri);
         for(int i=0;i<n;++i){
        cout<<a[i]<<" ";
    }  cout<<endl;
     }
 
}