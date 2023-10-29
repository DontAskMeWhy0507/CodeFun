#include <iostream>
using namespace std;
int main(){
    int n;cin>>n;
    int du=0;
    string s; cin>>s;
    string res="";
    int length = s.length();
    for(int i = length-1; i>=0; i--)
    {
        int tmp=s[i]-'0';
        int t = tmp*n+du;
      
    du=t/10;
          int chuso=t%10;
        res=char(chuso+'0')+res;
    }
   if (du) res = char (du + 48) + res;

        cout << res;
}