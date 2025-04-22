#include <format>
#include <iostream>

inline void Foo() {
    std::string fstr = std::format("inline function 1 {} {} {}", __FILE__, __LINE__, __func__);
    std::cout << fstr << std::endl;
}

void A() {
    Foo();
}
