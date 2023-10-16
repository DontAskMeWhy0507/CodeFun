while (true) //while(0) la gia tri sai, con lai deu la dung.
{ tong +=n;
n++;
if(n==0) break;   // ngat
//in ra cac so la boi cua 7 <=n
  int n;
cin>>n;
for(int i=7;i<=n; i+=7){
cout<<i<<" ";}
// ham bool
bool flag (false);
//con buom"
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin>>n;
for (int x=n;x>=-n;--x){
    for (int y =-n;y<=n;++y){
        cout<<(abs(y)>=abs(x) ? "* ": ". ");
    }
    cout<<endl;
}
    }
// ngoi sao:
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin>>n;
for (int x=n;x>=-n;--x){
    for (int y =-n;y<=n;++y){
        cout<<(abs(y)+abs(x)<=n ? "* ": ". ");
    }
    cout<<endl;
}
    }
//bai ham mu
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
int main(){
    int n;
    cin>>n;
 double e(0);
 double tmp(1);
 int i=1;
    while(tmp>=0.001){
     
           e+= tmp;
    tmp = tmp * (n/i);
    i++;
    }


cout<<tmp;
}


