#include <iostream>

class A {
public:
    A();
    A(int a) : a_{a} {}
    int F() const {
        return a_ * a_;
    }
private:
    int a_{10};
};

A::A() = default;

int main () {
    const A a(100);

    std::cout << a.F() << std::endl;

    return 0;
}
