#include <iostream>

class A {
public:
    A() = default;
    A(int a) : a_{a} {}
    ~A() = default;
    virtual void F() const = 0;
private:
    int a_{10};
};

void A::F() const {
    std::cout << "A::F" << std::endl;
}

int main() {
    A a;

    return 0;
}
