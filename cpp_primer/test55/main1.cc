#include <iostream>

// 编译器无法推断T1, 它未出现在函数形参列表中
template <typename T1, typename T2, typename T3>
T1 Sum(T2 a, T3 b) {
    std::cout << typeid(T1).name() << std::endl;
    std::cout << typeid(T2).name() << std::endl;
    std::cout << typeid(T3).name() << std::endl;
    return a + b;
}

int main() {
    int a = 1;
    long b = 2;
    auto val3 = Sum<long long>(a, b);

    return 0;
}
