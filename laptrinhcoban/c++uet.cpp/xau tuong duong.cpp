#include <iostream>
#include <string>
using namespace std;

bool isEquivalent(string s1, string s2) {
    int freq1[26] = {0}, freq2[26] = {0};
    for(char c : s1) freq1[c - 'a']++;
    for(char c : s2) freq2[c - 'a']++;
    for(int i=0;i<26;i++){
        if(freq1[i] != freq2[i]){
            return false;
        }
    }
    return true;
}

int main(){
    int T;
    cin>>T;
    cin.ignore();
    while(T--){
        string s;
        getline(cin,s);
        int count = 0;
        int dai=s.length();
        for(int len=1;len<dai;len++){
            for(int i=0;i<=dai-len;i++){
                for(int j=i+1;j<=dai-len;j++){
                    if(isEquivalent(s.substr(i, len), s.substr(j, len))){
                        count++;
                    }
                }
            }
        }
        cout << count << endl;
    }
}