//Dòng đầu tiên in ra các số trong dãy A theo thứ tự xuất hiện trong S, nếu không có phần tử nào thì in -1.
//Dòng thứ hai in ra các số chẵn lớn hơn hoặc bằng trung bình cộng của A theo giá trị tăng dần, nếu không có phần tử nào thì in -1.
#include <iostream>
#include <vector>
using namespace std;
int chuyen(string a)
{
    int len = a.length();
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        res = res * 10 + (a[i] - '0');
    }
    return res;
}

int main()
{
    string s;
    cin >> s;
    int len = s.length();
    vector <int> num;
    string tillnow = "";
    bool check = false;
    for (int i = 0; i < len; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            tillnow+=s[i];
        }
        else
        {
            if (tillnow != "")
            {
                int tmp = chuyen(tillnow);
                num.push_back(tmp);
                check = true;
            }
            tillnow = "";
        }
    }
    if (check == false)
        {
            cout << -1<<endl;
            return 0;
        }
    else
        {
        int sum = 0;
        for (int i = 0; i < num.size(); i++)
        {
            cout << num[i] << " ";
            sum += num[i];
        }
        cout <<endl;
        }
    check = false;
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] % 2 == 0&& num[i]>=sum/num.size())
        {
            cout << num[i] << " ";
            check  = true;
        }
    }
    if (check == false)
        {
            cout << -1;
        }


}