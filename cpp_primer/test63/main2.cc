#include <iostream>

// 1. Non-polymorphic Base Class (No virtual functions!)
class Base {
public:
    void sayHello() { std::cout << "Hello from Base\n"; }
    // Note: No virtual destructor or virtual methods here.
};

class Derived : public Base {
public:
    void sayHi() { std::cout << "Hi from Derived\n"; }
};

int main() {
    Base* ptr = new Derived();

    // 2. This line will cause a COMPILATION ERROR
    // Error: 'Base' is not a polymorphic type
    Derived* d = dynamic_cast<Derived*>(ptr); 

    if (d) {
        d->sayHi();
    }

    delete ptr;
    return 0;
}
