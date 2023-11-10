#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[n];
    int dem=0;
    int y=1,z=1,x=1,k=1;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]%2!=0&&a[i]>0){
            k=a[i];
        x=max(y,a[i]);
           y=a[i];
           dem++;
       }
    }
      for(int i=0;i<n;i++){
        if(a[i]%2!=0&&a[i]!=x){
        y=max(z,a[i]);
           z=a[i];
       }
    }
          
    for(int i=0;i<n;i++){
        if(dem==0) {
            cout<<"Day khong co so le.";
            return 0;}
        else if(dem==1){cout<<"Day co mot so le la: "<<k<<".";
        return 0;}
        else {
      
            cout<<"Hai so le lon nhat la: "<<x<<" va "<<y<<".";
            return 0;
        }
    } 
    
    
    
}