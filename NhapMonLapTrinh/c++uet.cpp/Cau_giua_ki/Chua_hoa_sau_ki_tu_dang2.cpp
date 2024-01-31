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