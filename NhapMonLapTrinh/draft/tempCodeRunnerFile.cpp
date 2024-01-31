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
vector<int> getCorrectResponse(vector<int>digitOfPin; vector<int>digitOfNum)
{
    vector<int> correctResponse;
    for(int i=0;i<9;i++){
        if(digitOfPin[i]==digitOfNum[i]){
            correctResponse.push_back(2);
        }
        else if(digitOfPin[i]!=digitOfNum[i]){
            correctResponse.push_back(1);
        }
        else{
            correctResponse.push_back(0);
        }
    }
}
void printfDigits(vector<int> digits)
{
    for (int i = 0; i < digits.size(); i++)
    {
        cout << digits[i] << " ";}
        
}
int main(){
    unsgined int pin, num;
    cin>>pin>>num;
    vector<int> digitsOfPin = getDigits(pin);
    vector<int> digitsOfNum =getDigits(num);
    vector<int> correctResponse = getCorrectResponse(digitsOfPin, digitsOfNum);
    printfDigits(correctResponse);
}