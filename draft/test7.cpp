#include <iostream>
#include <iomanip>
using namespace std;

struct Time
{
    int hour, minute, second;
    Time(int initHour, int initMinute, int initSecond)
    {
       hour=initHour;
       minute=initMinute;
       second=initSecond;
    }
    void getTimeDifference(Time other)
    {   
        int gio1=hour*3600+minute*60+second;
        int gio2=other.hour*3600+other.minute*60+other.second;
        int gio=abs(gio1-gio2);

        int h=gio/3600;
        int m=(gio%3600)/60;
        int s=(gio%3600)%60;
        Time Diff(0,0,0);
        Diff.hour=h;
        Diff.minute=m;
        Diff.second=s;
        cout<<setw(2) << setfill('0')<<Diff.hour<<":"<<setw(2) << setfill('0')<<Diff.minute<<":"<<setw(2) << setfill('0')<<Diff.second<<endl;
    }
};

int main()
{
    int hour, minute, second;
    cin >> hour >> minute >> second;
    Time time1(hour,minute,second);
    cin >> hour >> minute >> second;
    Time time2(hour,minute,second);
    time1.getTimeDifference(time2);
    return 0;
}
