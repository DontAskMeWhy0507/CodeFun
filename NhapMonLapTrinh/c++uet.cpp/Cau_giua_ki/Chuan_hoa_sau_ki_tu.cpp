#include <iostream>
using namespace std;
int main(){
    string s;
  getline(cin,s);
    s=" "+s;
    int n=s.length();
    for(int i=0;i<n;i++){
        s[i]=tolower(s[i]);
    }
    for(int i=0;i<n;i++){
        if(s[i]==' '&&s[i+1]!=' '){
            s[i+1]=toupper(s[i+1]);
        }
    }
    s[n]=' ';
    
   for(int i=0;i<n;i++){
        s[i]=s[i+1];
        }
    
    
    cout<<s;
}
