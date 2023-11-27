#include <iostream>
#include <cmath>
using namespace std;
int main(){
   long long int n;
    cin>>n;
    
        for(long long int a=1;a<=n;++a){
            long long int x=a*a*a*a*a;
            for(long long  int b=a+1;b<=n;++b){
                long long  int y=b*b*b*b*b;
                for(long long int c=b+1;c<=n;++c){
                    long long int z=c*c*c*c*c;
                    for(long long  int d=c+1;d<=n;++d){
                        long long int w=d*d*d*d*d;
                        for(long long  int i=n;i>d;--i){
                            long long int t=i*i*i*i*i;
                        if(t==x+y+z+w) cout<<a<<"^5 + "<<b<<"^5 + "<<c<<"^5 + "<<d<<"^5 = "<<i<<"^5 ";
                        break;
                    }
                }
            }
        }
    }
}