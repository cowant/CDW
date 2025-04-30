#include <string>
#include <iostream>
#include <format>

class C {
    friend std::ostream& operator << (std::ostream &out, const C &c) {
        std::string fstr = std::format("int: {} float: {}", c.i_, c.f_);
        out << fstr;
        return out;
    }
public:
    C() {
        std::string fstr0 = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr0 << std::endl;
    }
private:
    int i_;
    float f_;
};

int main() {
    C c1, c2;
    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;

    auto p0 = new (&c1) C;
    auto p1 = new (&c2) C();

    std::cout << *p0 << std::endl;
    std::cout << *p1 << std::endl;

    return 0;
}
