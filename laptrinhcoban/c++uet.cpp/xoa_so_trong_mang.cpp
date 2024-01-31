#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    double e = 0;
    double tmp = 1;
    int i = 1;
    while (tmp > 0.001) {
     
        tmp *= 1.0 * (n / i);
           e += tmp;
        i++;
    }
    cout << setprecision(4) << fixed << e;
    return 0;
}