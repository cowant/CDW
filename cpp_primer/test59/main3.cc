#include <iostream>

template<typename... Args>
auto sum(Args... args) {
    return (args + ...); // 一行搞定所有参数求和
}

int main() {
    sum(10, 10, 20);

    return 0;
}
