#include "A.h"
#include "B.h"

B::B() = default;
B::B(int a, const std::string &s) : a_{a}, s_{s} {}

B& B::CopyFrom(const A& a) {
    a_ = a.a_;
    s_ = a.s_;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const B& b) {
    std::string fstr = std::format("class B: {{{0} {1}}}", b.a_, b.s_);
    out << fstr << std::endl;
    return out;
}
