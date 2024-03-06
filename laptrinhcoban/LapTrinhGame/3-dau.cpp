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
  static Test* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Test();
        }
	static void foo()
	{
		std::cout << "Called static function: foo" << std::endl;
	}
  
private:
        static Test* s_Instance;

};

Test* Test::s_Instance = nullptr;

int main()
{
	// Cách gọi hàm foo
  /*Test::foo();
	return 0;*/

  // hoặc như sau

  /* Test* t = new Test;
    t->foo();
    delete t;
    return 0;*/

  // hoặc như sau

   /*Test::GetInstance()->foo();*/

    // Cách 2

    /*Test* instance = Test::GetInstance();
    instance->foo();
    // Không cần delete instance vì nó được quản lý bởi Test::GetInstance()
    return 0;*/
    Test trung;
    trung.foo();
}