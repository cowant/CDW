#include <iostream>

class A {
public:
    A() = default;
    A(int a) : a_{a} {}
    virtual ~A() = default;

    void FA() const {
        std::cout << "A @ " << this << std::endl;
    }

private:
    int a_{10};
};

class B : private A {
public:
    B() = default;
    explicit B(int b) : A(), b_{b} {}
    ~B() = default;

    void FB() const {
        FA();
        A *pa = new B(1000);
    }
private:
    int b_{30};
};

class C : public B {
public:
    C() = default;
    C(int c) : B(), c_{c} {}
    ~C() = default;

    void FC() const {
        FA();
        //A *pa = new B(1000);
    }
private:
    int c_{10000};
};

int main() {

    return 0;
}
