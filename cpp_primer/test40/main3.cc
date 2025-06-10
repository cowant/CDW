#include <iostream>

class B {
public:
    B() = default;
    B(int a) : a_{a} {}
    virtual ~B() {
        std::cout << "B destructor" << std::endl;
    }

private:
    int a_{0};
};

class D : public B {
public:
    D() = default;
    D(int a, int b) : B(a), b_{b} {}
    ~D() {
        std::cout << "D destructor"  << std::endl;
    }

private:
    int b_{100};
};

int main () {
    D d1(10, 20);

    return 0;
}
