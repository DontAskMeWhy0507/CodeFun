#include <iostream>
using namespace std;
int main()
{
    string s;
    getline(cin, s);
    stringstream ss (s);
    string token;
    stack<string> st;
    while(ss >> token)
    {
        st.push(token);
        
    }
}