///Bien đoi xau:
#include <iostream>

 

///daBcdC - s1    DABCDC
///ABCE  -s2

 

using namespace std;

 

bool is_In(string s1, string s2)
{
    int len1 = s1.length();

 

    for(int i = 0; i < len1; ++i)
    {
        if(isupper(s1[i])){
                size_t found = s2.find(s1[i]);///Tim ki tu s1[i] trong s2 bat dau tu ben trai
                if(found == string::npos) return false;
                s2 = s2.substr(found + 1);///Lay chuoi con tu vi tri (found + 1) ve cuoi
                ///cout << s2 << endl;///
        }
    }

 

    return true;
}

 

string is_changed (string s1, string s2)
{
    if(!is_In(s1, s2)) return "NO";///KT 1

 

    for(int i = 0; i < (int) s1.length(); i++) s1[i] = toupper(s1[i]);

 

    if(!is_In(s2, s1)) return "NO";///KT2

 

    return "YES";
}

 

int main()
{
    int Q; cin >> Q >> ws;

 

    while (Q--)
    {
        string s1, s2;
        cin >> s1 >> s2;
        cout << is_changed(s1, s2);
    }

 

    return 0;
}
 