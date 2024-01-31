#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n;
    cin>>n;
    int sum=0;
    vector <int> products(n);
    for (int  i=0;i<n;i++){
        cin>>products[i];
        sum += products[i];
    }
    float average= sum/n;

for (int product : products){                           // gán giá trị của vector vào biến product
    if (product> average) cout<< product<<" ";
}

}