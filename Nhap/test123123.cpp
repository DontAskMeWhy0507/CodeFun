#include <iostream>
using namespace std;

class shape 
{
    public:
        double demension;
        virtual double dientich() = 0;
};

class hinhtron: public shape
{
    public:
    
};

class hinhdep: public hinhtron
{
    public:
        virtual double dientich()
        {
            return 3.14 * demension * demension;
        }
};

int main()
{
    hinhdep h;
    h.demension = 3.14;
    cout << h.dientich();
    return 0;
}