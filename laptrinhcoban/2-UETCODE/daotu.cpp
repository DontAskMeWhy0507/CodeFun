#include <iostream>
using namespace std;

int main()
{
	string s;
	getline(cin, s);
	int n = s.length();
	int i, j = n-1;
	
	for(i = n-1; i >= 0; i--) {
		if(s[i] == ' ') { 
			for(int pos = i+1; pos <= j; pos++) cout << s[pos];
			j = i-1;
			cout << " ";
		}
		if(i == 0) {
			for(int pos = i; pos <= j; pos++) cout << s[pos];
		}
	}
}