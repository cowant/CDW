#include <iostream>

template <typename... Args>
std::ostream& log(std::ostream& out, const Args& ... args) {
    // out << arg1 << arg2 << arg3 << ... << argn
    return (out << ... << args);
}

int main() {
    log(std::cout, 1, 1.0, "hello") << std::endl;

    return 0;
}
