#include <iostream>

class A {
public:
    A() = default;
    A(int a, int b) : a_{a}, N{b} {
        std::cout << "A::A(int, int)" << std::endl;
    }

    A(const A&) = default;
    A& operator=(const A&) = default;

private:
    int a_ = 10;
    const int N = 100;
};

int main() {
    A a1(10, 100);

    A a2;

    a2 = a1;

    return 0;
}
