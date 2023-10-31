#include <iostream>
using namespace std;
int main(){
string s;
getline(cin,s);
int cnt=0;
s=" "+s;
int n=s.length();
for(int i=0;i<n;i++){
    if(s[i]==' '&& s[i+1] !=' ') cnt++;
}
cout<<cnt;
}