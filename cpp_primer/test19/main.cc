#include <iostream>
#include <string>
#include <vector>

int main () {
    // 接受单参数的const char*的string构造函数不是explicit的,可以用const char*
    // 拷贝初始化string
    std::string s = "a";

    // error, 接受一个容量参数的vector构造函数是explicit的，编译器不能将10
    // 自动转换为vector，无法执行拷贝初始化
    // std::vector<int> vec = 10;

    // 强制转换使用容量参数调用vector构造函数创建了一个临时对象
    std::vector<int> vec = static_cast<std::vector<int>>(10);
    std::cout << "size: " << vec.size() << std::endl;

    return 0;
}
