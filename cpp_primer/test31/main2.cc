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

class D : protected B {
public:
    D() = default;
    D(int i) : B(i), b_{i} {}
    ~D() = default;
private:
    int b_{100};
};

int main() {
    auto p = new D(10000);

    p->Addr();

    return 0;
}
