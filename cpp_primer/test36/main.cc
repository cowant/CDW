#include <iostream>

class B {
friend class F;
public:
    B() = default;
    B(int a) : a_{a} {}
    virtual ~B() = default;

    void Addr() const {
        std::cout << "B @ " << this << std::endl;
    }
private:
    int a_{0};
};

class D : public B {
public:
    D() = default;
    D(int a, int b) : B(a), b_{b} {}
    ~D() = default;

    void Addr() const {
        std::cout << "D @ " << this << std::endl;
    }
private:
    int b_{100};
};

class F {
public:
    F() = default;

    void Func(const D &d) const {
        std::cout << d.a_ << std::endl;
    }
};

int main() {
    D d(100, 200);

    F f;

    f.Func(d);

    return 0;
}
