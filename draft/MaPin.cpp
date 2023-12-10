#include <iostream>
#include <vector>
#include <algorithm>///reverse

using namespace std;

vector<int> getDigits(unsigned int number)
{
    vector <int> vt;
    while (number)
    {
        vt.push_back(number%10);
        number /= 10;
    }
    reverse(vt.begin(), vt.end());
    return vt;
}

void printDigits(vector<int> digits)
{
    for(auto x: digits)
        cout << x;
    cout << endl;
}

vector<int> getCorrectResponse(vector<int> pin, vector<int> num)
{
    vector <int> vt;
    for(auto i = 0; i < pin.size(); ++i)
        vt.push_back(num[pin[i]]);

        return vt;
}

int main()
{
    unsigned int pin, num;
    cin >> pin >> num;

    vector<int> digitsOfPin = getDigits(pin);
   /// printDigits(digitsOfPin);

    vector<int> digitsOfNum = getDigits(num);
   /// printDigits(digitsOfNum);

    vector<int> correctResponse = getCorrectResponse(digitsOfPin, digitsOfNum);
    printDigits(correctResponse);

    return 0;
}



//vector <int> vt; /// vt.size() == 0 - MANG DONG
//for (int i  = 0; i < n; ++i)
//{
//    cin >> x;
//    vt.push_back(x);///DUA x vao cuoi vt, tang size vt len 1
//}
//
//for (int i = 0; i < vt.size(); ++i)
//{
//    cout << vt[i] << ' ';
//    ///cout << vt.at(i);
//}
//
//for(auto x: vt)
//{
//    cout << x << ' ';
//}
//
//int n;
//cin >> n;
//
//vector <int> vt(n);///vt.size () = n - MANG TINH
//
//for (int i = 0; i <n; ++i)
//    cin >> vt[i];
