#include <iostream>
using namespace std;

bool isPalindrome(int num) {
    int reversedNum = 0, originalNum = num;
    while (num > 0) {
        int digit = num % 10;
        reversedNum = reversedNum * 10 + digit;
        num /= 10;
    }
    return (originalNum == reversedNum);
}

int main() {
    int n;
   cout << "Enter the size of the array: ";
cin >> n;

int arr[n];
cout << "Enter the elements of the array: ";
for (int i = 0; i < n; i++) {
    cin >> arr[i];
}

int countPalindrome = 0;
for (int i = 0; i < n; i++) {
    if (isPalindrome(arr[i])) {
        countPalindrome++;
    }
}

if (countPalindrome > 0) {
    cout << "yes" << endl;
} else {
    cout << "no" << endl;
}
}