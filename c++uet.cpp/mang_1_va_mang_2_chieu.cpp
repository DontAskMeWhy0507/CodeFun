#include <iostream>
using namespace std;
int main(){
    int n; cin>>n;
    int a[n];
    /*for (int i=0;i<n;i++){
        cin>>a[i];  
    }*/
    for(int &x :a){ // &x : tham chieu
        cin>>x;
    }
    for (int x:a){      // for each : lay tung phan tu trong mang a
        cout<<x<<" ";
    }
}