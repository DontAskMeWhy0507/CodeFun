#include <iostream>
using namespace std;

class Message {
public:
    virtual void Print() const = 0;
};

class HelloMessage : public Message {
public:
    void Print() const  {
        cout << "Hello, World!" << endl;
    }
};

int main() {
    HelloMessage hello;
    hello.Print();
    return 0;
}
/*#include <iostream>
#include <string>
using namespace std;

// Base class
class Vehicle {
  public: 
    string brand = "Ford";
    void honk() {
      cout << "Tuut, tuut! \n" ;
    }
};

// Derived class
class Car: public Vehicle {
  public: 
    string model = "Mustang";
};

int main() {
  Car myCar;
  myCar.honk();
  cout << myCar.brand + " " + myCar.model;
  return 0;
}

*/