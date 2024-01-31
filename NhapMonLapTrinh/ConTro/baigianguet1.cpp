    #include <iostream>
    using namespace std;
    void squareValue(int x) {           //truyền tham trị
     x = x * x; 
    }

    void squareByRef(int &x){           //truyền tham chiếu
        x = x * x;
    }

    void squareByPtr(int *ptr) {        //truyền thaam trị địa chỉ của x vào hàm
     *ptr = *ptr * *ptr;                //*ptr ở đây (toán tử giải tham chiếu)  là giá trị biến con trỏ trỏ vào , còn *ptr ở trên là gọi ra con trỏ ptr;
    }

    int main() {
     int x = 5;
     squareValue(x);
     cout << x << " la ket qua truyen tham tri,dia chi cua x la  " << (&x) << endl;     
     squareByRef(x);
     cout << x << " la ket qua truyen tham chieu,dia chi cua x la " << (&x) << endl;    
     squareByPtr(&x);                       //truyền tham trị địa chỉ của x vào hàm
     cout << x << " la ket qua truyen tham tri,dia chi cua x la " << (&x) << endl;     
    }   