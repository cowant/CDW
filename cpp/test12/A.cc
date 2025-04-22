#include "A.h"

A::A() = default;
A::A(int a, const std::string &s) : a_{a}, s_{s} {}

std::ostream& operator<<(std::ostream &out, const A& a) {
    std::string fstr = std::format("class A: {{{0} {1}}}", a.a_, a.s_);
    out << fstr << std::endl;
    return out;
}
