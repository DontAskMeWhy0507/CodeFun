#include <iostream>
using namespace std;
int main(){
int i = 0;

while (i < 10) {
  cout << i << "\n";
  i++;
  if (i == 4) {
    break;
  }
}


i=0;
while (i < 10) {
  
  cout <<"Continue: "<< i << "\n";
  i++;
  if (i == 4) {
    i++;
    continue;
  }
}

}