#include <iostream>
using namespace std;
int main(){
    long long arr[100];
    for(int i=1;i<20;i++){
        arr[i]=i*i*i;
    }
    
    long long N;
    cin>>N;
    for(long long n=1;n<N;n++)
    {
        for(long long a=1;a<20;a++)
        {
            for(long long b=a+1;b<20;++b)
            {
                if(arr[a]+arr[b]==n)
                for(long long c=a+1;c<20;++c)
                {
                    for(long long d=c+1;d<20;++d)   
                    {
                        if(arr[c]+arr[d]==n)
                        {
                            cout<<n<<" ";
                            break;
                        }
                    }
                }
            }
        }
    }
}