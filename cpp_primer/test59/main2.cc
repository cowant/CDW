#include <iostream>
#include <utility>

void F(int&& i) {
    std::cout << "F(int&&)" << std::endl;
}

void wrapper(int&& i) {
    F(std::forward<int>(i));
}

int main() {
    wrapper(10);

    return 0;
}
