// có 3 file pentagon.h và mathematics.h và file main của project pentagon.cpp
/* tên file: pentagon.h
int getting_pentagon_side() 
{ 
    return 5; 
}
*/

/* tên file:  mathematics.h
#include "pentagon.h" 
*/

/*  tên file : pentagon.cpp
#include <iostream> 
#include "mathematics.h" 
#include "pentagon.h" 
using namespace std; 
int main() 
{ 
    return 0; 
}
*/

// để sửa lỗi do lặp lại trên ta dùng syntax sau
#ifndef HEADER_H_NAME
#define HEADER_H_NAME
/*...
...*/
#endif

// sau khi sửa lỗi

/* file pentagon.h
#ifndef PENTAGON_H
#define PENTAGON_H
int getting_pentagon_side() 
{ 
    return 5; 
}

*/

/* file mathematics.h
#ifndef MATHEMATICS_H
#define MATHEMATICS_H
#include "pentagon.h"
#endif
*/

/* file pentagon.cpp
#include <iostream>
#include "mathematics.h"
#include "pentagon.h"
using namespace std;
int main()
{
    int i{getting_pentagon_side()};
    cout << i;
    return 0;
}
*/
