#include "B.h"

B::B(std::ostringstream &out) : out_{out} {}

void B::Display() const {
    std::string fstr = std::format("after serialize: {}", out_.str());
    std::cout << fstr << std::endl;
}

// 这里要注意，B的成员函数B::Serialize作为A的友元，需要定义在A.cc里面，
// 因为在B.cc里面，我们并不能看到A的完整声明
