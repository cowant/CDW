#include <iostream>
#include <format>

class A {
public:
    A(int a, int b) : a_{a}, b_{b} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }
private:
    int a_;
    int b_;
};

class B {
public:
    B(int a0, int a1, int a2, int a3) : a_{a0}, b_{a1}, c_{a2, a3} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    // const成员必须在初始化列表初始化
    B(int a) : b_{a}, c_{a, a} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    // 引用必须在初始化列表初始化
    B(int a0, int a1) : a_{a0}, c_{a0, a1} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    // 未提供默认构造函数的类类型必须在初始化列表初始化
    B(int a0, int a1, int a2) : a_{a0*a1}, b_{a2} {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }
private:
    const int a_;
    int &b_;
    A c_;
};

int main() {
    B b(1, 2, 3, 4);

    return 0;
}
