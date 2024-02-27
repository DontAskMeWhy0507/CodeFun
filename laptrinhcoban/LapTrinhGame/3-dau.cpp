/*#include <iostream>
using namespace std;

class Car {
  public:
    int speed(int maxSpeed);
};

int Car::speed(int maxSpeed) {
  return maxSpeed;
}

int main() {
  Car myObj; // Create an object of Car
  cout << myObj.speed(200); // Call the method with an argument
  return 0;
}*/
#include <iostream>

struct Test
{
	static void foo()
	{
		std::cout << "Called static function: foo" << std::endl;
	}
};

int main()
{
	//Test::foo();
	//return 0;
   Test* t = new Test;
    t->foo();
    delete t;
    return 0;
}