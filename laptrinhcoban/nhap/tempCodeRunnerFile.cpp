#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int tmp=0;
    int res=0;
    while (n)
    {   

        res+=n%2;
        res*=10;
        n/=2;
    }
    cout<<res;
}