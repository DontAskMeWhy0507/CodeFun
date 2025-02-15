#include <iostream>
 
void incrementAndPrint()
{
    static int s_value = 1; // static duration variable
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but became inaccessible
 
int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();
    
    return 0;

    // Output: 2 3 4 do s_value la bien toan cuc
}