#include <iostream>
#include <format>

class B {
public:
    B(int a, int b, int c, int d) : a_{a}, b_{b}, c_{c}, d_{d} {
        std::string fstr = std::format("4 arguments: {} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    B(int a, int b, int c) : B(a, b, c, 0) {
        std::string fstr = std::format("3 arguments: {} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    B(int a, int b) : B(a, b, 0) {
        std::string fstr = std::format("2 arguments: {} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    B(int a) : B(a, 0) {
        std::string fstr = std::format("1 argument: {} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    B() : B(0) {
        std::string fstr = std::format("0 argument: {} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

private:
    int a_;
    int b_;
    int c_;
    int d_;
};

int main() {
    B a;

    return 0;
}
