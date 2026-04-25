#include <iostream>

template<typename T>
void Foo(const T& t) {
    std::cout << t << std::endl;
}

template <typename... Args>
void ActionOnAll(Args... args) {
    int dummy[] = {(Foo(args), 0)...};
    (void)dummy;
}

int main() {
    ActionOnAll(1, "xxxx", 10.45);
    return 0;
}
