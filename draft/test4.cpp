   #include <iostream>
    using namespace std;
//PHAN 1
    /* int main()
 {
     int x = 5;
     cout << x << " " << (&x) << " " << *(&x) << endl;

    return 0;
 } */                                                    // 5 0x7ffeeb0b0a3c 5
//PHAN 2
    /* int main(){
     int x = 5;
     int *ptr = &x;  
cout << "gia tri x la "<< x << ", gia tri (&x) la " << (&x) << ", gia tri ptr la " << ptr << ", gia tri (&ptr) la " << (&ptr) << ", gia tri (*ptr) la " << (*ptr) << ", gia tri &(*ptr) la " << &(*ptr) <<  endl;  
     *ptr = 10;
     cout << x << " " << (&x) << " " << (&ptr) << " " <<*ptr << endl;
 } */
 //PHAN 3 
    /*void swapByValue(int a, int b) {
     int tmp = a;
     a = b;
     b = tmp;
 }

 void swapByPtr(int *a, int *b) {
     int tmp = *a;
     *a = *b;
     *b = tmp;
 }

 int main() {
     int x = 5, y = 6;
     cout << x << " " << (&x) << " " << y << " " << (&y) << endl; // 5 6
     swapByValue(x, y);
     cout << x << " " << (&x) << " " << y << " " << (&y) << endl; // 5 6
     swapByPtr(&x, &y);
     cout << x << " " << (&x) << " " << y << " " << (&y) << endl; // 6 5
 } */
//PHAN 4
/*int main(){
     int x = 5;
     int *ptr = &x;
     int **pptr = &ptr;
     cout << (&x) << " " << (&ptr) << " " << *(&ptr) << " " << (&pptr) << " " << *pptr << " " << **pptr << endl;
    
     return 0;
 }*/
 //PHAN 5
 int main(){
     string str[5] = { "ab", "bc", "cd", "de", "ef"};
     string *p = str;
    
     cout << p << " " << *p << " " << (&p) << endl;
     p++; // p -> str[1]
    cout << p << " " << *p << " " << (&p) << endl;
    p += 2; // p -> str[3]
   cout << p << " " << *p << " " << (&p) << endl;
     p--; // p -> str[2]
   cout << p << " " << *p << " " << (&p) << endl;
   cout << (p - str) << endl; // 2
    cout << *(p + 2) << endl; // str[5]
   cout << p[0] << endl; // str[2]
    cout << p[2] << endl; // str[4]
 }