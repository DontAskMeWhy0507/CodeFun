#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline character after n
    unordered_map<string, int> mp;
    string s;
    for (int i = 0; i < n; i++)
    {
        getline(cin, s);
        stringstream ss (s);
        string name;
        string lastName;
        while (ss >> name)
        {
            lastName = name; // Keep updating lastName until the end of the line
        }
        mp[lastName]++;
    }

    int maxCount = 0;
    for (auto &p : mp) {
        maxCount = max(maxCount, p.second);
    }

    for (auto &p : mp) {
        if (p.second == maxCount) {
            cout << p.first << " ";
        }
    }

    return 0;
}




/*
    1. substr()
    s = s.substr(1, 3); // s = "bcd" thì s chỉ chứa 3 kí tự bắt đầu từ vị trí 1

    2. find()
     size_t pos = s.find("abc");
    if (pos != string::npos) {
        cout << "Found at position: " << pos;
    } else {
        cout << "Not found";
    } 

    3. replace()
    s.replace(1, 3, "xyz"); // s = "abcdedgh" thì s sẽ thay thế 3 kí tự bắt đầu từ vị trí 1 bằng "xyz" => s = "axyzdefgh"

    4. insert()
    s.insert(1, "xyz"); // s = "abcdefgh" thì s sẽ chèn chuỗi "xyz" vào vị trí 1 => s = "axyzbcdefgh"

    5. erase()
    s.erase(1, 3); // s = "abcdefgh" thì s sẽ xóa 3 kí tự bắt đầu từ vị trí 1 => s = "afgh"

*/





// void daotu(char* p)
// {
//     int n = strlen(p);
//     for(int i = 0; i < n / 2; i++)
//     {
//         char tmp = p[i];
//         p[i] = p[n - i - 1];
//         p[n - i - 1] = tmp;
//     }
// }

// int main ()
// {
//     char p[10] = "123456789";               // Phải khai báo 10 do còn có kí tự là '\0' ơ cuối chuỗi
//     daotu(p);
//     cout << p << endl;
// }
// Hàm substring
// Hàm substring trả về chuỗi con của chuỗi gốc, bắt đầu từ vị trí pos và có độ dài len.
// Cú pháp:
// string substr(int pos, int len) const;

