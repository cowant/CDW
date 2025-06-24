#include "tp.hpp"
#include <iostream>

int main() {
    std::initializer_list<int> l2 = {1, 2, 3, 4};
    auto p1 = std::make_shared<A<int>>(l2);

    std::initializer_list<std::string> l3 = {"aaa", "bbb", "ccc", "ddd"};
    auto p2 = std::make_shared<A<std::string>>(l3);

    B<int> b1(p1);
    B<std::string> b2(p2);

    b1.Clear(1);
    b2.Clear(1);

    return 0;
}
