#include <iostream>
#include <cmath>
using namespace std;
int main (){
    int a;
    cin>>a;
    int i=0;
    while (i*i<=a){

        if (i*i==a) {cout<< "yes"; 
            return 0;              //dong chuon trinh luon khong chay o duoi
        }
        i++;
      
    } 
    cout <<"no";

}