#include <iostream>
using namespace std;
int main(){
    int n; //321
    cin>>n;
    int sohangtram = n/100;
    int sohangchuc = (n/10)- sohangtram*10;
    int sohangdonvi = n- sohangtram*100-sohangchuc*10;
    int nphay= sohangdonvi*100 + sohangchuc*10+sohangtram;
    if (sohangtram>sohangdonvi){
    int b= n- nphay;
    int tram= b/100;
    int chuc=b/10- tram*10;
    int donvi= b -tram*100 - chuc*10;
    int bphay = donvi*100 + chuc*10 + tram;
    cout<< b+ bphay;
}
else cout<<"invalid";}