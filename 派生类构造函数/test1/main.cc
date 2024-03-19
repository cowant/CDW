#include <iostream>

struct B {
    int a_{0};
};

struct D : B {
    D(int a, const std::string &s) : a_{a}, name_{s} {}
    std::string name_;
};

int main() {
    D d(12, "hello");

    return 0;
}
