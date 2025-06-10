#include <iostream>

class B {
public:
    B() = default;
    B(int a) : a_{a} {
        F();
    }
    virtual ~B() {
        F();
    }

    virtual void F() const {
        std::cout << "B::F" << std::endl;
    }

private:
    int a_{0};
};

class D : public B {
public:
    D() = default;

    D(int a, int b) : B(a), b_{b} {
        F();
    }

    ~D() {
        F();
    }

    void F() const override {
        std::cout << "D::F" << std::endl;
    }
private:
    int b_{100};
};

int main () {
    D d1(10, 20);

    std::cout << "###" << std::endl;

    return 0;
}
