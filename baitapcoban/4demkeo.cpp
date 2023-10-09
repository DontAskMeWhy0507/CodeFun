#include <iostream>
using namespace std;
int main (){
    int n;
    int a[1000];
    int s=0;
    cin>>n;
    for( int i=1;i<=n;i++){
        cin>>a[i];
        s = a[i]+ s;
    }
    cout<< s;
}