#include <iostream>
using namespace std;
int main(){
/*  int a=100;
    int *ptr;                             // khai bao con tro ptr
    if(ptr == nullptr){                   // có thể dùng NULL thay cho nullptr nghĩa là con trỏ không gán cho gì
        cout<<"con tro null !\n";
    } */



    int a=100;
    int *ptr = &a;                      // con trỏ chỉ vào địa chỉ của biến a (&a là địa chỉ của biến a)
    /* có thể khai báo cách khác  int *ptr;  ptr =&a;  */
    cout<<"Gia tri cua bien dang tro toi "<<(*ptr)<<endl;             // cái này nó sẽ truy cập đến giá trị của biến mà con trỏ đang trỏ tới. Có nghĩa là (*ptr) tương đương với biến ;
    (*ptr)++;
    cout<<"Gia tri cua bien sau khi +1 la "<<a<<endl;
    int *ptr2=&a;                  // có thể gán *ptr2=ptr;
    cout<<"Dia chi cua bien a "<<&a<<endl;
    cout<<"Gia tri cua con tro ptr "<<ptr<<endl;
    cout<<"Gia tri cua con tro ptr2 "<<ptr2<<endl;
    

}