#include <iostream>

std::ostream& log(std::ostream& out) {
    return out;
}

template <typename T, typename... Args>
std::ostream& log(std::ostream& out, const T& t, const Args& ... args) {
    out << t << " ";
    return log(out, args...);
}

int main() {
    log(std::cout, 1, 1.0, "hello") << std::endl;

    return 0;
}
