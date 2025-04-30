#include <iostream>

class A {
public:
    A() const = default;
    A(int a) const : a_{a} {}
    int F() const {
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
