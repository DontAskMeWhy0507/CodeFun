#include <iostream>
using namespace std;
void vehinh() {
    int n;
    cin>>n;
for (int x=n;x>=-n;--x){
    for (int y =-n;y<=n;++y){
        cout<<(abs(y)>=abs(x) ? "* ": ". ");
    }
    cout<<endl;
}
    }

int main(){
    int n;
    cin>>n;
    for (int x=n;x>=-n;--x){
    for (int y =-n;y<=n;++y){
        cout<<(abs(y)+abs(x)<=n ? "* ": ". ");
    }
    cout<<endl;
    //dung ham vehinh() de ve hinh khac
}
}