#include <iostream>
#include <format>

class A {
public:
    A(int a, int b, int c, int d) : a_{a}, b_{b}, c_{c}, d_{d} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    A() : A(0, 0, 0, 0), a_{0} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    A(int a) : a_{a}, A(a, a, a, a) {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

private:
    int a_;
    int b_;
    int c_;
    int d_;
};

int main() {
    A a(10);

    return 0;
}
