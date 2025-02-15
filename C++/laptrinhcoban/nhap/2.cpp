#include <iostream>
#include <cstring>
using namespace std;

void daotu(char p)
{
    int n = strlen(p);
    for(int i = 0; i < n / 2; i++)
    {
        char tmp = p[i];
        p[i] = p[n - i - 1];
        p[n - i - 1] = tmp;
    }
}

int main ()
{
    char p[10] = "123456789";
    daotu(p);
    cout << p << endl;
}