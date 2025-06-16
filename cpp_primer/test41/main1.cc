#include <iostream>

template <double v> void F() {
    std::cout << v << std::endl;
}

int main() {
    F<8.0>();

    return 0;
}
