//đề bài nhập vào chữ số a và một số nguyên b rất lớn, in ra tích của a và b;
#include <iostream>
using namespace std;
int main(){
    int n;cin>>n;
   int du = 0;
    string s; cin>>s;
    string res="";
    int length = s.length();
    for (int i = length - 1; i >= 0; --i)
    {
        int tmp = s[i] - '0';
        int t = tmp *n + du;//45
        du = t/10;
        int dv = t % 10;
        res = char (dv + '0') + res;
    }

    if (du) res = char (du + '0') + res;

        cout << res;
}