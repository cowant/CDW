#include <iostream>

template <typename... Args>
void iterate(Args... args) {
    ([](const auto& item){
        std::cout << item << std::endl;
    }(args), ...);
}

int main() {
    iterate(10, "xxxx", 10.35);
    return 0;
}
