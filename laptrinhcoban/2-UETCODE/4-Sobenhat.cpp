#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int len = s.length();
    char Min = '9';
    int vitri;
    bool change = false;
    for(int i = 1; i < len; i++)
    {
        if(s[i] < s[0] && s[i] <= Min && s[i] != '0')
        {
            Min = s[i];
            vitri = i;
            change = true;
        }
    }
    if(change)
    {
        swap(s[0], s[vitri]);
        cout << s;
        return 0;
    }
    for(int i = 1; i < len; i++)
    {
        for(int j = i + 1; j < len; j++)
        {
            if(s[j] < s[i] && s[j] <= Min )
            {
                Min = s[j];
                vitri = j;
                change = true;
            }
        }
        if(change)
        {
            swap(s[i], s[vitri]);
            cout << s;
            return 0;
        }
    }
    cout << s;
}