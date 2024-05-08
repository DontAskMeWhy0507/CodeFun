#include <iostream>
using namespace std;
int main(){
    string s;
    getline(cin,s);
    int l=s.length();
    string result;
    int i=0;
 if(s[0]==' '){
 do
     {
    result = s[i]+ result;
    i++;
}
 
 while(s[i]==' '&&s[i+1]==' ');}
for (int i = 0; i < l; i++) {
    if (s[i] == ' ' && s[i + 1] == ' ') {
        continue;
    }
    result += s[i];
}

cout << result << endl;

return 0;

}
/*
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
*/