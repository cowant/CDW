#include <iostream>


struct A {
    A() {
        std::cout << "A::A() contructs A @" << this << std::endl; 
    }

    ~A() {
        std::cout << "A::~A() destructs A @" << this << std::endl; 
    }
};

struct B {
    B() {
        std::cout << "B::B() contructs B @" << this << std::endl; 
    }

    ~B() {
        std::cout << "B::~B() destructs B @" << this << std::endl; 
    }
};

struct C {
    C() {
        std::cout << "C::C() contructs C @" << this << std::endl; 
    }

    ~C() {
        std::cout << "C::~C() destructs C @" << this << std::endl; 
    }
};

class D {
public:
    D() {
        std::cout << "D::D() contructs D @" << this << std::endl; 
    }

    ~D() {
        std::cout << "D::~D() destructs D @" << this << std::endl; 
    }
private:
    A a_;
    B b_;
    C c_;
};



int main() {
    D d;


    return 0;
}
