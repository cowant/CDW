#include <iostream>

class B {
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

class D : private B {
public:
    D() = default;
    D(int a, int b) : B(a), b_{b} {}
    ~D() = default;

    using B::Addr;

private:
    int b_{100};
};

int main() {
    D d(100, 200);

    d.Addr();

    return 0;
}
