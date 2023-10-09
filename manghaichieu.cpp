#include <iostream>
#include <vector>
using namespace std;
int main(){
    int i,j;
    int ncot,mhang,qcauhoi;
    cin>>mhang>>ncot>>qcauhoi;
    vector <vector <int> > a(mhang,vector<int> (ncot));
    for ( i=0;i<mhang;i++){
        for ( j=0;j<ncot;j++){
            cin>>a[i][j];
        }
    }
int b[qcauhoi][2];
int h,k;
for( h=0;h<qcauhoi;h++){
    for ( k=0;k<2;k++){
        cin>>b[h][k];
    }
}
int hang=-1,cot;
for ( h=0;h<qcauhoi;h++){
    for(k=0;k<2;k++){
        cot= b[h][k];
        if(hang==-1){
            hang=cot;
        }
    }
    cout<<a[hang][cot]<<endl;
    hang=-1;
}
return 0;
}