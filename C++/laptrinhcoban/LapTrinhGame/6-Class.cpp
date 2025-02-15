//  Thừa kế có 2 loại. 1 là lấy luôn hàm từ phương thức cha, 2 là viết lại hàm từ phương thức cha.
//Cách hai thì mỗi phương thức con sẽ có một hàm riêng, còn cách 1 thì chỉ cần viết một hàm duy nhất cho tất cả các phương thức con. 
//Syntax: virtual float calculateArea()=0; ở lớp cha, và ở lớp con là float calculateArea() { return dimension * dimension; }
//nếu có thêm const : virtual float calculateArea() const = 0; ở lớp cha, và ở lớp con là float calculateArea() const { return dimension * dimension; }
#include <iostream>
using namespace std;
//Abstract class
class Shape{
protected:
	float dimension;
public:
	void getDimension(){
        cin >> dimension;
    }
    // pure virtual Function
    virtual float calculateArea() = 0;
};
// Derived class
class Square : public Shape{
public:
    float calculateArea() {
        return dimension * dimension;
    }
};
// Derived class
class Circle : public Shape{
public:
    float calculateArea() {
        return 3.14 * dimension * dimension;
    }
};
void main(){
	Square square;
    Circle circle;
    cout << "Enter the length of the square: ";
    square.getDimension();
    cout << "Area of square: " << square.calculateArea() << endl;
    cout << "\nEnter radius of the circle: ";
    circle.getDimension();
    cout << "Area of circle: " << circle.calculateArea() << endl;
	system("pause");
}