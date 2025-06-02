#include <iostream>

class B {
public:
    B() = default;
    B(int i) : a_{i} {}
    virtual ~B() = default;
    void Addr() const {
        std::cout << "object @ " << this << std::endl;
    }
private:
    int a_{10};
};

class D1 : public B {
public:
    D1() = default;
    D1(int i) : B(i), b_{i} {}
    ~D1() = default;

    void Foo() const {
        B b = *this;
        b.Addr();
    }
private:
    int b_{100};
};

class D2 : protected B {
public:
    D2() = default;
    D2(int i) : B(i), b_{i} {}
    ~D2() = default;

    void Foo() const {
        B b = *this;
        b.Addr();
    }
private:
    int b_{100};
};

class D3 : private B {
public:
    D3() = default;
    D3(int i) : B(i), b_{i} {}
    ~D3() = default;

    void Foo() const {
        B b = *this;
        b.Addr();
    }
private:
    int b_{100};
};

int main() {
    auto p1 = new D1(10000);
    auto p2 = new D2(20000);
    auto p3 = new D3(30000);

    p1->Foo();
    p2->Foo();
    p3->Foo();

    return 0;
}
