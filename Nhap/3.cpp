#include <iostream>
#include <iomanip>

class Time
{
private:
    int gio, phut, giay;
    int sum; // Total seconds

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
    friend std::ostream& operator<<(std::ostream& os, const Time& t)
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