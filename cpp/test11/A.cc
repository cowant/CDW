#include "A.h"

A::A() = default;

A::A(int a, int b) : a_{a}, b_{b} {}

void A::Display() const {
    std::string fstr = std::format("a: {} b{}", a_, b_);
    std::cout << fstr << std::endl;
}

void B::Serialize(const A& a) {
    out_ << "#" << "int:" << a.a_ << "#" << "int:" << a.b_;
}
