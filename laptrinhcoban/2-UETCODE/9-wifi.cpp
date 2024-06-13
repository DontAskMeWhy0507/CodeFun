/*
Tuyến phố thông minh Anna có n tòa nhà, tòa nhà thứ i có khoảng cách xi mét so với đầu của tuyến phố. 
Thành phố quyết định sẽ đặt các trạm phát sóng wifi miễn phí tại các tòa nhà dọc theo tuyến phố thông minh.
Mỗi thiết bị phát wifi có thể phủ sóng trong phạm vi k mét, 
tức là các tòa nhà có khoảng cách đến thiết bị không vượt quá k mét thì sẽ sử dụng được wifi từ thiết bị này. 
Bạn hãy viết chương trình tìm cách đặt các trạm wifi để số lượng trạm wifi là ít nhất và tất cả các tòa nhà đều có thể sử dụng wifi.

Đầu vào
Dữ liệu vào từ bàn phím gồm 2 dòng. Dòng đầu tiên chứa 2 số nguyên n,k(n,k≤105)
Dòng thứ hai chứa n số nguyên xi (xi≤105)
Đầu ra

In ra  màn hình số lượng thiết bị phát wifi ít nhất để tất cả các tòa nhà đều có thể sử dụng wifi.
Với VD1 bên dưới ta có thể đặt wifi tại tòa nhà ở tọa độ 2 và 5 (tối ưu nhất), hoặc 2 và 4.
Với VD2: ta có thể đặt wifi tại tòa nhà ở tọa độ 3 và 6 (tối ưu nhất), hoặc (2, 5), hoặc (2, 6). */
/**Author: No name*/

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int a[100001];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort (a, a+n);

    int cnt(0);
    int start;

    for (int i = 0; i < n;)///Thay bằng while hoặc do ... while đều được
    {
        start = a[i];
        i++;
        while (i < n && a[i] <= start + k) i++; /// bo qua cac nha co the dung chung wifi voi i

        i --; ///Lui lai 1 vi tri de dat wifi
        cnt ++; ///tang bien dem

        start = a[i];
        while (i < n && a[i] <= start + k) i++; /// bo qua cac nha co the dung chung wifi voi nha i
    }

    cout << cnt;

    return 0;
}
