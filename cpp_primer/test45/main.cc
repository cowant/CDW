#include "tp.hpp"
#include <iostream>

int main() {
    A<int> a = {1, 2, 3, 4};
    A<std::string> b = {"aaa", "bbb", "ccc", "ddd"};

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}
