    #include <iostream>
    using namespace std;
    void squareValue(int x) {
     x = x * x;
    }

    void squareByRef(int &x){
        x = x * x;
    }

    void squareByPtr(int *ptr) {
     *ptr = *ptr * *ptr;
    }

    int main() {
     int x = 5;
     squareValue(x);
     cout << x << " " << (&x) << endl;     
     squareByRef(x);
     cout << x << " " << (&x) << endl;    
     squareByPtr(&x);
     cout << x << " " << (&x) << endl;     
    }