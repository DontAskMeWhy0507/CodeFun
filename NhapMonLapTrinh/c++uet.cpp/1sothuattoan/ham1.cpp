#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
  /*Thuat toan min max*/  
    cout<<min({2,3,4,5,6,7})<<endl;
                 int a[5]={6,7,9,12,22};
    cout<<min(a[2],a[4])<<endl;
    cout<<min_element(a,a+5)<<endl;    // tra ve dia chi cua phan tu nho nhat
    cout<<*min_element(a,a+5)<<endl;   // tra ve gia tri cua phan tu nho nhat
                  vector <int> b={2,3,4,5,6,7};
    cout<<min(b[2],b[4])<<endl;

    cout<<*min_element(begin(b),end(b))<<endl;   // tra ve gia tri cua phan tu nho nhat
/*thuat toan */
}