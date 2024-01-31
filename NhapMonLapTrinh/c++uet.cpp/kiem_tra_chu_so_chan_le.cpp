#include <iostream>
using namespace std;
int main(){
  int n; cin>>n;
  int a[100];
  int demsole[10]={0};
  int demsochan[10]= {0};
   
  for (int i=0;i<n;i++){
    cin>>a[i];
    
  while (a[i]>0){               //Vì khi chia cho 10 liên tục, số cuối cùng là chia cho 10 sẽ làm tròn thành số 0 (do là kiểu int)
  int chuso=a[i]%10;
  
  if(chuso%2==0){
    demsochan[i]++;
  }
  else if(chuso%2!=0){
    demsole[i]++;
  }
  a[i]=a[i]/10;
  }

  }
for(int i=0;i<n;i++){
cout << demsochan[i] << " " << (demsole[i])<<endl;
}

}