#include <iostream>
#include <iomanip>
using namespace std;
class Time
{

    int gio, phut, giay;
    int sum;

public:
    Time(int _gio = 0, int _phut = 0, int _giay = 0) : gio(_gio), phut(_phut), giay(_giay)
    {
        sum = gio * 3600 + phut * 60 + giay;
        gio = sum/3600;
        phut = (sum%3600)/60;
        giay = sum%60;
    }

    int hour() const
    {
        return gio;
    }

    int minute() const
    {
        return phut;
    }

    int second() const
    {
        return giay;
    }

    // Overloaded output operator
    friend ostream& operator<<(std::ostream& os, const Time& t)
    {
        os << std::setw(2) << std::setfill('0') << t.gio << ':' << std::setw(2) << t.phut << ':' << std::setw(2) << t.giay;
        return os;
    }

    // Comparison operators
    friend bool operator<(const Time& a, const Time& b)
    {
        return a.sum < b.sum;
    }

    friend bool operator>(const Time& a, const Time& b)
    {
        return a.sum > b.sum;
    }

    friend bool operator<=(const Time& a, const Time& b)
    {
        return a.sum <= b.sum;
    }

    friend bool operator>=(const Time& a, const Time& b)
    {
        return a.sum >= b.sum;
    }

    friend bool operator==(const Time& a, const Time& b)
    {
        return a.sum == b.sum;
    }

    friend bool operator!=(const Time& a, const Time& b)
    {
        return a.sum != b.sum;
    }
};
// 
/*class Message {
public:
    virtual void Print() const = 0;
};

class HelloMessage : public Message {
public:
    void Print() const  {
        cout << "Hello, World!" << endl;
    }
};

int main() {
    HelloMessage hello;
    hello.Print();
    return 0;
}*/