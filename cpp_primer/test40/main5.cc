#include <iostream>
#include <string>
#include <format>

class B {
public:
    B() = default;
    B(int a) : a_{a}, b_{a} {}
    B(int a, int b) : a_{a}, b_{b} {}
    virtual ~B() = default;

protected:
    int a_{5};
    int b_{10};
};

class D : public B {
friend std::ostream& operator<<(std::ostream& out, const D& d);
public:
    // using声明继承基类的构造函数
    using B::B;
    D() = default;
    ~D() = default;
};

std::ostream& operator<<(std::ostream& out, const D& d) {
    std::string fstr = std::format("{} {}", d.a_, d.b_);
    out << fstr;
    return out;
}

int main () {
    D d1(10, 20);
    D d2(100);

    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl;

    return 0;
}
