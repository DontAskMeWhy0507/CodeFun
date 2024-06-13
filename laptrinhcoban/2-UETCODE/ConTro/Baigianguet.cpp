/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;

// int main()
// {
//     int x = 5;
//     cout << x << " " << (&x) << " " << *(&x) << endl;

//     return 0;
// }

// int main(){
//     int x = 5;
//     int *ptr = &x;
//     cout << x << " " << (&x) << " " << ptr << " " << (&ptr) << " " << (*ptr) << " " << &(*ptr) <<  endl;
//     *ptr = 10;
//     cout << x << " " << (&x) << " " << (&ptr) << " " <<*ptr << endl;
// }

/* Parameter Passing by Reference */
// void squareValue(int x) {
//  x = x * x;
// }

// void squareByRef(int &x){
//     x = x * x;
// }

// void squareByPtr(int *ptr) {
//  *ptr = *ptr * *ptr;
// }

// int main() {
//  int x = 5;
//  squareValue(x);
//  cout << x << " " << (&x) << endl; // 5
//  squareByRef(x);
//  cout << x << " " << (&x) << endl; // 25
//  squareByPtr(&x);
//  cout << x << " " << (&x) << endl; // 625
// }

// void swapByValue(int a, int b) {
//     int tmp = a;
//     a = b;
//     b = tmp;
// }

// void swapByPtr(int *a, int *b) {
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// int main() {
//     int x = 5, y = 6;
//     cout << x << " " << (&x) << " " << y << " " << (&y) << endl; // 5 6
//     swapByValue(x, y);
//     cout << x << " " << (&x) << " " << y << " " << (&y) << endl; // 5 6
//     swapByPtr(&x, &y);
//     cout << x << " " << (&x) << " " << y << " " << (&y) << endl; // 6 5
// }

/* Const pointer 

int const* is pointer to const int
int *const is const pointer to int
int const* const is const pointer to const int
Using this rule, even complex declarations can be decoded like,

int ** const is a const pointer to pointer to an int.
int * const * is a pointer to const pointer to an int.
int const ** is a pointer to a pointer to a const int.
int * const * const is a const pointer to a const pointer to an int.

*/
// int main(){
//     int x = 5;
//     const int y = 10;
//     const int z = 8;
    
    // int const *ptr = &y;
    // cout << y << " " << (&y) << " " << *ptr << " " << (&ptr) << endl;
    // *ptr = &z;
    // cout << z << " " << *ptr << endl;

    // const int *ptr = &x;
    // cout << x << " " << (&x) << " " << *ptr << " " << (&ptr) << endl;
    // // x = 5;
    // // cout << x << " " << (&x) << " " << *ptr << " " << (&ptr) << endl;
    // *ptr = 10;
    
    // int * const ptr = &x;
    // cout << x << " " << (&x) << " " << *ptr << " " << (&ptr) << endl;
    // *ptr = 10;
    // cout << x << " " << (&x) << " " << *ptr << " " << (&ptr) << endl;
    // ptr = &y;
    // cout << y << " " << (&y) << " " << *ptr << " " << (&ptr) << endl;
    
    // const int * const ptr = &x;
    // *ptr = 10;
    // *ptr = &y;
// }

// int main(){
//     int x = 5;
//     int *ptr = &x;
//     int **pptr = &ptr;
//     cout << (&x) << " " << (&ptr) << " " << *(&ptr) << " " << (&pptr) << " " << *pptr << " " << **pptr << endl;
    
//     return 0;
// }

/* Pointer & Array */
// // int main(){
//     string str[5] = { "ab", "bc", "cd", "de", "ef"};
//     string *p = str;
    
//     cout << p << " " << *p << " " << (&p) << endl;
//     p++; // p -> str[1]
//     cout << p << " " << *p << " " << (&p) << endl;
//     p += 2; // p -> str[3]
//     cout << p << " " << *p << " " << (&p) << endl;
//     p--; // p -> str[2]
//     cout << p << " " << *p << " " << (&p) << endl;
//     cout << (p - str) << endl; // 2
//     cout << *(p + 2) << endl; // str[5]
// //     cout << p[0] << endl; // str[2]
// //     cout << p[2] << endl; // str[4]
// // }

/* Dynamic allocation*/
// int main ()
// {
//   int i,n;
//   int * p;
//   cout << "How many numbers would you like to type? ";
//   cin >> n;
//   p= new (nothrow) int[n];
//   if (p == nullptr)
//     cout << "Error: memory could not be allocated";
//   else
//   {
//     for (i=0; i<n; i++)
//     {
//       cout << "Enter number: ";
//       cin >> p[i];
//     }
//     cout << "You have entered: ";
//     for (i=0; i<n; i++){
//       cout << p[i];
//       if(i < n-1)
//           cout << ", ";
//     }
//     delete[] p;
//   }
//   return 0;
// }

/* Binary file */
#include<fstream>
struct Student {
  int sid;
  const char* name;
};
int main() {
  ofstream wf("student.dat", ios::out | ios::binary);
  if(!wf) {
      cout << "Cannot open file!" << endl;
      return 1;
  }
  Student wstu[3];
  wstu[0].sid = 1;
  wstu[0].name = "An Nguyen";
  
  wstu[1].sid = 2;
  wstu[1].name = "Hoang Le";
  
  wstu[2].sid = 3;
  wstu[2].name = "Trung Pham";
  
  for(int i = 0; i < 3; i++)
      wf.write((char *) &wstu[i], sizeof(Student));
      
  wf.close();
  if(!wf.good()) {
      cout << "Error occurred at writing time!" << endl;
      return 1;
  }
   
  ifstream rf("student.dat", ios::binary);
  if(!rf) {
      cout << "Cannot open file!" << endl;
      return 1;
  }
  Student rstu[3];
  for(int i = 0; i < 3; i++)
      rf.read((char *) &rstu[i], sizeof(Student));
  rf.close();
  if(!rf.good()) {
      cout << "Error occurred at reading time!" << endl;
      return 1;
  }
  cout<<"Student's Details:"<< endl;
  for(int i=0; i < 3; i++) {
      cout << "ID: " << rstu[i].sid << endl;
      cout << "Name: " << rstu[i].name << endl;
      cout << endl;
  }
  return 0;
}





1