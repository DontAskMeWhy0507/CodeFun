#include <iostream>
 
void incrementAndPrint()
{
    int value = 1; // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here
 
int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();
    
    return 0;

    // Output: 2 2 2 do value la bien local cua incrementAndPrint
}