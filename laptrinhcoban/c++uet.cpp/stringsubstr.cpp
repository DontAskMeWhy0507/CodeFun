//Khi làm bài tập đặt câu với các vị thần Hy Lạp, Hercules đã vô tình viết sai tên của cha mình là thần Zeus thành "Zues". 
//Hãy viết chương trình giúp Hercules sửa lại những chỗ viết sai này.

#include <iostream>
#include <string>
using namespace std;
int main()
{
    string text;
    getline(cin,text);
    int len=text.length();
    for(int i=0;i<len;i++)
    {
        if(i>len-5||text.substr(i,4) != "Zues")
        {
            cout<<text[i];
        }
        else {
            cout<<"Zeus";
            i+=3;
        }
    }
}