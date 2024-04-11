/*#include <iostream>
#include <cmath>

using namespace std;
string next_ver(string &str)
{
    int n = str.length();
    int i = n-1;
    while (i >= 0 && str[i] == '1') {
            str[i] = '0';
            i--;
        }

     if(i>=0)   {
            str[i] = '1';
    }
    return str;
}

int main()
{
    int n;
    cin >> n;
    string str("");

    for(int i =0; i < n; ++i) str = "0" + str;
    cout << str << endl;

    n = pow(2.0, n*1.0);
    //cout << n << endl;
    n--;
    while (n--)
    {
        cout << next_ver(str) << endl;
    }
    return 0;
}*/

#include <iostream>
#include <cmath>

using namespace std;
//string next_ver(string &str)
//{
//    int n = str.length();
//    int i = n-1;
//    while (i >= 0 && str[i] == '1') {
//            str[i] = '0';
//            i--;
//        }
//
//     if(i>=0)   {
//            str[i] = '1';
//    }
//    return str;
//}

void back_Tracking(string &str, const int &n)
{
    if((int)str.length() == n) {
        cout << str << endl;
        return;
    }
    for (char i ='0'; i <= '1'; ++i)
    {
        str = str + i;///doi sang ki t
        back_Tracking(str, n);
        str.erase(str.length()- 1);
    }
}

void back_Tracking1(string &str, int n)
{
    if(n == 0) {
        cout << str << endl;
        return;
    }
    for (char i ='0'; i <= '1'; ++i)
    {
        str = str + i;///doi sang ki t
        back_Tracking(str, n-1);
        str.erase(str.length()- 1);
    }
}


int main()
{
    int n;
    cin >> n;

    string str("");

    //back_Tracking(str, n);
    back_Tracking1(str, n+1);
    return 0;
}
