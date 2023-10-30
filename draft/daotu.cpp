#include <iostream>
using namespace std;

int main()
{
	string myStr;
	getline(cin, myStr);
	int n = myStr.size();
	int i, j = n-1;
	
	for(i = n-1; i >= 0; i--) {
		if(myStr[i] == ' ') { 
			for(int pos = i+1; pos <= j; pos++) cout << myStr[pos];
			j = i-1;
			cout << " ";
		}
		if(i == 0) {
			for(int pos = i; pos <= j; pos++) cout << myStr[pos];
		}
	}
}