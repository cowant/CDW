#include <iostream>

class Printer {
public:
    void printHello() { std::cout << "Hello!" << std::endl; }
    void printValue(int x) { std::cout << "Value: " << x << std::endl; }
};

int main() {
    // 1. 声明并赋值
    void (Printer::* funcPtr)() = &Printer::printHello;
    void (Printer::* funcWithArg)(int) = &Printer::printValue;

    Printer myPrinter;

    // 2. 调用（注意必须加括号，因为 . 和 -> 的优先级高于 *）
    (myPrinter.*funcPtr)();          // 输出 Hello!
    (myPrinter.*funcWithArg)(42);    // 输出 Value: 42

    return 0;
}
