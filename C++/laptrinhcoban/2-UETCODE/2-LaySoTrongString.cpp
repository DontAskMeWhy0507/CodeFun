#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string s;
    cin >> s;
    vector <int> a;
    int len = s.length();
    for(int i = 0; i < len ; i++)
    {
        if(isdigit(s[i]))
        {
            string temp = "";
            while(isdigit(s[i]) && i < len)
            {
                temp += s[i];
                i++;
            }
            a.push_back(stoi(temp));
        }
    }
    for(int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
}