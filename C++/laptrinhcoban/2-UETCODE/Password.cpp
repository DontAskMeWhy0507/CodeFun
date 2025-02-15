#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> getDigits(unsigned int num)
{
    int digit;
    vector<int> digits;
    while (num > 0)
    {
        digit = num % 10;
        digits.push_back(digit);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}
vector<int> getCorrectResponse(vector<int>digitOfPin, vector<int>digitOfNum)
{
    vector<int> correctResponse;
    int len = digitOfPin.size();
    for (int j=0; j< len;j++)
    {
        for (int i = 0; i <=9; i++)
        {
        if (digitOfPin[j]==i)
        {
            correctResponse.push_back(digitOfNum[i]);
        }
        }
    }
    return correctResponse;
}
void printDigits(vector<int> digits)
{
    for (int digit : digits)
    {
        cout << digit;
    }
}
int main(){
    unsigned int pin, num;
    cin>>pin>>num;
    vector<int> digitsOfPin = getDigits(pin);
    vector<int> digitsOfNum =getDigits(num);
    vector<int> correctResponse = getCorrectResponse(digitsOfPin, digitsOfNum);
    printDigits(correctResponse);
}