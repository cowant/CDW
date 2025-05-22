#include <iostream>

class A {
public:
    A() = default;
    A(int a, int b) : a_{a}, b_{b} {}
    virtual ~A() = default;

protected:
    int a_{10};
    int b_{20};
};

class B : private A {
public:
    B() = default;
    explicit B(int c) : A(), c_{c} {}
    ~B() = default;

    void F() const {
        A *pa = new B(1000);
    }
private:
    int c_{30};
};

int main() {
    A *pa = new B(40);

    return 0;
}
