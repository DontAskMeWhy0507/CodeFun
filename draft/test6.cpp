#include <cstring>
#include <iostream>
using namespace std;
void trim_right(char *s){
    int len=strlen(s);
    for(int i=0;i<len;i++){
        if(s[i]==' ')break;
    }
}
int main(){
    char s[100];
    cin.getline(s,100);
    trim_right(s);
    cout<<s;
}   