#include <iostream>
using namespace std;

int fibonacci (int n)   // co 1 ham f(x)

{
    int f1=1;
    int  f2=1;
    int i=3;        //day la so thu tu cua day fibonacci
    int fn;         //day la so ở số thứ tự i
    while (i<=n)
    {
        fn =f1+f2;    
        f1=f2;      //f1 là kết quả, f2 là phép tính , khác hoàn toàn f2=f1
        f2=fn;
        i++;
    }
    return fn;      // return fn là trả hàm về giá trị của fn 
}
int  main (){
   int n;
   cin>>n;
   cout << fibonacci(n);
    }
   
