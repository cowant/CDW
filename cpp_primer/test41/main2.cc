#include <iostream>

template <int v> inline void F() {
    std::cout << v << std::endl;
}

int main() {
    F<8>();

    return 0;
}
