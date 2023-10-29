#include <iostream>
using namespace std;
int main(){
    int n; cin>>n;
    int a[n+1];
    bool tang=false,giam=false,vodanh=false;
    for (int i=0;i< n;i++){
        cin >> a[i];
    }
     
    for(int i=0;i<n-1;i++){
        if(a[i]>a[i+1]){
            giam=true;
        }
        else if(a[i]<a[i+1]){
            tang=true;
        }
        else {
            vodanh=true;
        }
}
    if(vodanh||tang&&giam){
        cout<<"Vo Danh";
        return 0;
    }
        else if(giam){cout<<"giam"; }
    else {cout<<"tang";}



}