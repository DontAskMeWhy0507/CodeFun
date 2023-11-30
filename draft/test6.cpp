#include <iostream>
using namespace std;
int main (){
   int x;
   int f1=1,f2=1,fn;
   int n;
   cin>>n;
   for(int i=0;i<n;i++){
       fn=2*f1-f2;
       f1=f2;
       f2=fn;
   }
   cout<<fn;
}