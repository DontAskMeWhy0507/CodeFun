#include <iostream>
#include <iomanip>
using namespace std;

struct date {
    int day, month, year;
    date(int _day, int _month, int _year) {
        day = _day;
        month = _month;
        year = _year;
    }

    bool isValid() {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            return false;
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            daysInMonth[2] = 29;
        return day <= daysInMonth[month];
    }

    date getNextDay() {
        if (!isValid()) {
            cout << "INVALID" << endl;
            return *this;
        }
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            daysInMonth[2] = 29;
        day++;
        if (day > daysInMonth[month]) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        return date(day, month, year);
    }

    void inputDate() {
        char slash;
        cin >> day >> slash >> month >> slash >> year;
    }
};

int main() {
    date today(1, 1, 2000);  // Initialize with any valid date
    today.inputDate();
    date tomorrow = today.getNextDay();
    if (tomorrow.isValid())
        cout << setw(2) << setfill('0') << tomorrow.day << "/"
             << setw(2) << setfill('0') << tomorrow.month << "/"
             << tomorrow.year << endl;
    return 0;
}