#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    long long i, j;
    long long ncot, mhang;
    cin >>mhang >> ncot ;
    int b[mhang][ncot];
    for (i = 0; i < mhang; i++) {
        for (j = 0; j < ncot; j++) {
            cin >> b[i][j];
        }
    }
    cout<<b[1][2];
    }