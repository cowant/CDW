#include <iostream>

class A {
public:
    A() = default;
    A(int a) : a_{a} {}
    int F() {
        return a_ * a_;
    }
private:
    int a_{10};
};

int main () {
    const A a(100);

    std::cout << a.F() << std::endl;

    return 0;
}
