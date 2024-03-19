#include <iostream>

// 定义重载的Foo函数

void Foo(int) = delete;

void Foo(double) {
    std::cout << "Foo(double)" << std::endl;
}

int main() {
    Foo(10.0);

    // 重载决议将会匹配到void Foo(int) 版本
    Foo('c');
    Foo(true);

    return 0;
}
