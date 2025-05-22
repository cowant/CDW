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

class B : public A {
public:
    B() = default;
    B(int b) : A(), b_{b} {}
    ~B() = default;

    void F() const override {
        std::cout << "B::F" << std::endl;
    }
private:
    int b_{1000};

};

int main() {
    A *a = new B(120);

    a->F();

    return 0;
}
