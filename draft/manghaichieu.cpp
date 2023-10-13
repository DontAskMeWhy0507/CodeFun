#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    long long i, j;
    long long ncot, mhang, qcauhoi;
    cin >>mhang >> ncot >> qcauhoi;
    int b[mhang][ncot];
    for (i = 0; i < mhang; i++) {
        for (j = 0; j < ncot; j++) {
            cin >> b[i][j];
        }
    }
    long long h,k;
    int a[qcauhoi][2];
    for (h = 0; h < qcauhoi; h++) {
        for (k = 0; k < 2; k++) {
            cin >> a[h][k];
        }
    }
    long long hang=-1, cot;
    for (h = 0; h < qcauhoi; h++) {
        for (k = 0; k < 2; k++) {
            cot = a[h][k]-1;
            cout<<"day la cot trong vong "<<cot<<endl;
            if (hang==-1)
            {
                hang = cot;
                cout<<"day la hang trong vong "<<hang<<endl;
            }
        }
        cout<<"day la cot "<<cot<<endl;
       // cout << b[hang][cot] << endl;
       

        hang =-1;
    }
    return 0;
}