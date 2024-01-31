#include <iostream>

using namespace std;

main()
{
    int x = 10;
    int & x_reference = x;
	
    cout << "Giá trị của x: " << x << endl;
    cout << "Giá trị của tham chiếu tới x: " << x_reference << endl;
	
    cout << "Địa chỉ của x: " << &x << endl;
    cout << "Địa chỉ của tham chiếu tới x: " << &x_reference;   //cùng kết quả với &x do tham chiếu tới x
    
}
//https://viblo.asia/p/lap-trinh-c-co-ban-bai-9-con-tro-phan-1-dia-chi-ao-tham-chieu-va-con-tro-trong-c-aWj53xqwK6m