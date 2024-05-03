#include <iostream>
using namespace std;
bool check (char a)
{
    if(a>=0&&a<=9)return true;
    return false;
}
int main()
{
    int a = 0,b = 0;
    string fraction;
    cin >> fraction;
    int len = fraction.length();
    while(len--)
    {
        if(fraction[len] == '/') break;
        if(!check(fraction[len])) throw "Bad fraction string.";
        int tmp = fraction[len] - '0';
        b *= 10;
        b += tmp;
    }
    while(len--)
    {
        if(!check(fraction[len])) throw "Bad fraction string.";
        int tmp = fraction[len] - '0';
        a *= 10;
        a += tmp;
    }
}