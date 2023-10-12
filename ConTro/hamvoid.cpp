#include <iostream>
using namespace std;
void float1(int x){
    x*=2;
}

void float2(int &x){
    x*=2;
}

void float3(int *x){
    (*x)*=2;            //*x ở đây (toán tử giải tham chiếu)  là giá trị biến con trỏ trỏ vào , còn *x ở trên là gọi ra con trỏ x;

} 
int main(){
    int a=100;
    float1(a);
    cout<<a<<endl;
    float2(a);
    cout<<a<<endl;
    float3(&a);
    cout<<a<<endl;

}