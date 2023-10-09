#include <iostream>
using namespace std;

int main() {
  int n, a[100];
  int sum = 0;
 cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
  }

  float average = sum / float(n);
  for (int i=0; i<=n;i++){
      if (a[i]>=average){ cout<< a[i] <<" ";
          
      }
  }
}