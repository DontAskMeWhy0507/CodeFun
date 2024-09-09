#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ll m, w, p, n;
    cin >> m >> w >> p >> n;

    ll res = LLONG_MAX;
    ll candy = 0;
    ll passes = 0;

    while (candy < n)
    {
        // Time to next purchase or completion
        ll time = (p - candy) / (m * w);
        if ((p - candy) % (m * w) != 0)
        {
            time++;
        }

        // Check if we can complete before next purchase
        if (candy + time * m * w >= n)
        {
            res = min(res, passes + (n - candy + m * w - 1) / (m * w));
            break;
        }

        // Update for next purchase
        passes += time;
        candy += time * m * w;

        // Buy as many machines as possible
        ll buy = candy / p;
        candy -= buy * p;
        if (m <= w)
        {
            m += buy;
        }
        else
        {
            w += buy;
        }
    }

    cout << res;
    return 0;
}