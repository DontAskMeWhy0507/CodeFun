#include <iostream>
using namespace std;
int main(){
string s;
getline(cin,s);
int cnt;
s=" "+s;
int n=s.length();
for(int i=0;i<n;i++){
    if(s[i]==' '&&S[i+1] !=' ') cnt++;
}
cout<<cnt;
}