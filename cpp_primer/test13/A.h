#ifndef _A_H_
#define _A_H_

#include <iostream>
#include <string>
#include <format>

class A {
public:
    A() = default;
    A(int a, const std::string &s) : a_{a}, s_{s} {}

    friend void F1() {
        std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
        std::cout << fstr << std::endl;
    }

    void F2() {
        F1();
    }

private:
    int a_{10};
    std::string s_{"A"};
};

#endif
