//tim so lan chuyen n dia tu a sang b voi c la trung gian
#include <iostream>
using namespace std;
int solanchuyen(int n){
    if(n==1)return 1;
    return (2*solanchuyen(n-1)+1);
}
int main(){
    int n;
    cin>>n;
    cout<<solanchuyen(n);
    return 0;
}