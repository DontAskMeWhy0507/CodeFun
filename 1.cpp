#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream in ("2.txt");
    string s;
    int n = 0;
    while (getline(in, s)) {
        if (s.find("*   **") == 0){
            n++;
        }       
    }

    in.close();
    cout << n << endl;
    return 0;

}