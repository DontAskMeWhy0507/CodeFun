#include <iostream>
using namespace std;

int value = 1;

int main()	{

	int value = 10;

	cout << "local value: " << value << endl;
	cout << "global value: " << ::value << endl;
	
	return 0;
}