#include <iostream>

template <typename... Args>
void print(Args... args) {
    std::cout << sizeof...(Args) << std::endl;
}

int main() {
    print(1, 1, 1, 1);
    return 0;
}
