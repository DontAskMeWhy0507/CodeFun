#include <iostream>
using namespace std;

int main(){
    int a;
    cin >> a;
    float arr[a];
    if(a < 0){
        cout <<"invalid";
        return 0;
    }
    for(int i = 0; i < a; i++){
        cin >> arr[i];
        if(arr[i] < 0|| arr[i]>1){
            cout <<"invalid";
            return 0;
        }
    }
    int cs[a];
    for(int i = 0; i < a; i++){
        cs[i] = i;
    }
    for(int i = 0; i < a; i++){
        for(int  j = 0; j < a; j++){
            if(arr[i] > arr[j]){
                float tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                int tmp1 = cs[i];
                cs[i] = cs[j];
                cs[j] = tmp1;
            }
        }
    }

    if(arr[0] < 0.05){
        cout << "No one is alive.";
    }
    else{
        for(int i = 0; i < a; i++){
            if (arr[i] > 0.05){
                cout << cs[i] << " ";
                for(int j = i+1; j < a; j++){
                    arr[j] = arr[j]/2;
                }
            }
        }
    }

}