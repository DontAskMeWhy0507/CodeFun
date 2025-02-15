#include <limits.h>
int findRadius(vector<int> houses, vector<int> heaters)
{
    int n=houses.size();
    int m=heaters.size();
    int MAX=INT_MIN;
    for(int i=0;i<n;i++)
    {
        int MIN=INT_MAX;
        for(int j=0;j<m;j++)
        {
            MIN=min(MIN,abs(houses[i]-heaters[j]));
            MAX= max(MAX,MIN);
        }
    }
    return MAX;
}