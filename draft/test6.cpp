#include <iostream>
using namespace std;
int insert(int arr[], int n, int pos, int value)
{
 for (int i = n; i >= pos; i--) {
 arr[i] = arr[i-1];
 }
 
 return n+1;
}
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
    int vitri;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(a[i]<b[j+1]&&a[i]>b[j]){
              m=insert(b, n, j+1, int a[i]);  
            }
        }
    }
        for(int i=0;i<n+m;i++){
        cout<<b[i];
    }
}