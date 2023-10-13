#include <iostream>

using namespace std;

 /*int main()
 {
   int x = 5;
    cout << x << " " << (&x) << " " << *(&x) << endl;

   return 0;
}*/

  int main(){
      int x = 5;
      int *ptr = &x;
      cout << x << " " << (&x) << " " << ptr << " " << (&ptr) << " " << (*ptr) << " " << &(*ptr) <<  endl;
      *ptr = 10;
      cout << x << " " << (&x) << " " << (&ptr) << " " <<*ptr << endl;
  }
