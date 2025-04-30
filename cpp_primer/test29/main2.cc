#include <iostream>

class A {
public:
    A() = default;
    A(int a, int b) : a_{a}, b_{b} {
        std::cout << "A::A(int, int)" << std::endl;
    }

    A(const A&) = default;
    A& operator=(const A&) = default;

private:
    int a_ = 10;
    int &b_;
};

int main() {
    A a1;

    return 0;
}
