#include <iostream>

class B {
public:
    B() = default;
    B(int i) : a_{i} {}
    virtual ~B() = default;
    void Addr() const {
        std::cout << "object @ " << this << std::endl;
    }

protected:
    void B_Protected() const {
        std::cout << "B::Protected" << std::endl;
    }

private:
    int a_{10};
};

class D : protected B {
public:
    D() = default;
    D(int i) : B(i), b_{i} {}
    ~D() = default;

protected:
    void D_Protected() const {
        std::cout << "D::Protected" << std::endl;
    }

private:
    int b_{100};
};

class DD : protected D {
public:
    DD() = default;
    DD(int i) : D(i), c_{i} {}
    ~DD() = default;

    void Foo() const {
        B_Protected();
        D_Protected();
    }

private:
    int c_{100};
};

int main() {
    auto p = new DD(10000);

    p->Foo();

    return 0;
}
