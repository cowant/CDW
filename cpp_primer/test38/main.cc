#include <iostream>

class B {
public:
    B() = default;
    B(int a) : a_{a} {}
    virtual ~B() = default;

    virtual void Vfunc() const {
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

    virtual void Vfunc(int i) const {
        std::cout << "D @ " << this << std::endl;
    }
private:
    int b_{100};
};

int main() {
    B *p = new D(100, 200);

    p->Vfunc();

    return 0;
}
