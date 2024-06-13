/*
nhi phan co do dai n

#include <iostream>
using namespace std;

int n;
int a[100];

void inkq(){
    for(int i = 1;i <= n;i++){
        cout << a[i];
    }
    cout << endl;
}

void Try(int i){
    for(int j =0;j <= 1;j++){
        a[i] = j;
        if(i == n){
            inkq();
        }
        else Try(i+1);
    }
}

int main()
{
    cin >> n;
    Try(1);
    
}
*/


/*
n chu so 0 va m chu so 1

#include <iostream>
#include <string>
using namespace std;

int n, m;
int a[100];
int cn, cm;

void print() {
    for (int i = 1; i <= n + m; i++)
        cout << a[i];
    cout << endl;
}

void Try(int i) {
    for (int j = 0; j < 2; j++) {
        if ((j == 0 && cn > 0) || (j == 1 && cm > 0)) {
            a[i] = j;
            if (j == 0) cn--;
            else cm--;
            if (i == n + m) {
                print();
            } else {
                Try(i + 1);
            }
            if (j == 0) cn++;
            else cm++;
        }
    }
}

int main() {
    cin >> n >> m;
    cn = n;
    cm = m;
    Try(1);
    return 0;
}
*/

/*
Hoan vi cua 1 xau ki tu

#include <iostream>
#include <algorithm>
using namespace std;

void hoanvi(string s,int j,int l)
{
    if(j==l)
    {
        cout<<s<<endl;
    }
    else
    {
        for(int i=j;i<=l;i++)
        {
            swap(s[j],s[i]);
            sort(s.begin()+l+1,s.end());
            hoanvi(s,j+1,l);
           
        }
    }
}

int main()
{
    string s;
    cin>>s;
    int len=s.length();
    hoanvi(s,0,len-1);
}
*/



/*
tat ca cac xau tu cac ki tu trong string 

#include <iostream>
#include <string>
using namespace std;

void generate(string chars, int length, string &res) {
    if ((int)res.length() == length) {
        cout << res << endl;
        return;
    }
    for (char c : chars) {
        res = res + c;
        generate(chars, length, res);
        res.erase(res.length()-1);
    }
}

int main() {
    string chars;
    cin >> chars;
    string res("");
    for (int len = 1; len <= (int)chars.length(); ++len) {
        generate(chars, len, res);
        res = "";
    }
    return 0;
}
*/


/*
Me Cung 

//MECUNG
#include <bits/stdc++.h>

using namespace std;

int n, m;
int a[20][20], mark[20][20];

bool solve(int x, int y)
{
    if(x == n-1 && y == m-1){
        mark[x][y] = 1;
        return true;
    }

    if(a[x][y] == 1 || mark[x][y] == 1 || x < 0 || x >= n || y < 0 || y >= m) return false;

    mark[x][y] = 1;///CHON THU

    if(solve(x+1, y)) return true;
    if(solve(x, y+1)) return true;
    if(solve(x-1, y)) return true;
    if(solve(x, y-1)) return true;

    mark[x][y] = 0;///QUAY LUI

    return false;
}

void printf()
{
    for (int i = 0; i < n; ++i){
        for (int j =0; j < m; ++j)
        {
            if(mark[i][j] == 1) cout << "2 ";
            else
                cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for(int j = 0; j < m; ++j)
    {
        cin >> a[i][j];
        mark[i][j] = 0;
    }

    if(solve(0, 0))
    {
      printf();
    }
    else
    {
        cout << "KHONG THAY";
    }

}
*/