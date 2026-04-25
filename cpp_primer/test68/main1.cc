#include <iostream>
#include <string>

void someFunction() {
    // 局部类定义
    class Logger {
    public:
        void log(const std::string& msg) {
            std::cout << "[Local Log]: " << msg << std::endl;
        }
    };

    Logger myLogger; // 在函数内部实例化
    myLogger.log("Hello from a local class!");
} // 函数结束，Logger 类也随之销毁

int main() {
    someFunction();
    // Logger x; // 错误！main 函数无法访问 Logger
    return 0;
}
