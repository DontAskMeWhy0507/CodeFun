#include <iostream>
using namespace std;

class Message {
public:
    virtual void Print() const = 0;
};

class HelloMessage : public Message {
public:
    void Print() const override {
        cout << "Hello, World!" << endl;
    }
};

int main() {
    HelloMessage hello;
    hello.Print();
    return 0;
}