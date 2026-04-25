// main.cpp
#include <iostream>

// 关键点：告诉 C++ 编译器这个函数在别处是用 C 方式定义的
//extern "C" {
//    void add_numbers(int a, int b);
//}
void add_numbers(int a, int b);

int main() {
    std::cout << "在 C++ 中调用 C 函数..." << std::endl;
    add_numbers(10, 20);
    return 0;
}
