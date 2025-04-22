#include <format>
#include <iostream>

void Foo() {
    std::string fstr = std::format("inline function 2 {} {} {}", __FILE__, __LINE__, __func__);
    std::cout << fstr << std::endl;
}

void B() {
    Foo();
}
