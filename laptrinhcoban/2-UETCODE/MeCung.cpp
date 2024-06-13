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