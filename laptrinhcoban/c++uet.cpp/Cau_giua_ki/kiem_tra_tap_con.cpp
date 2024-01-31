#include <iostream>
using namespace std;
int main(){
    int m,n;
    cin>>m;
    int a[m];
    for(int i=0;i<m;i++){
        cin>>a[i];
    }
    cin>>n;
    int b[n];
     for(int i=0;i<n;i++){
        cin>>b[i];
    }

for(int i=0;i<n-m+1;i++){
    int kt=0;
           for(int k=0;k<m;k++){
               if(a[k]==b[k+i]){
                   kt++;
                  }
               }
               if(kt==m) {cout<<"YES"; return 0;}
           }
           cout<<"NO";
       }