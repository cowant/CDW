#include <iostream>

void F(int&& i) {
    std::cout << "F(int&&)" << std::endl;
}

void wrapper(int&& i) {
    F(i);
}

int main() {
    wrapper(10);

    return 0;
}
