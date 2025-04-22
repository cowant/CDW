#include <iostream>
#include <format>
#include <array>

int main() {
    // int i{}; 执行值初始化，对于基本类型，值初始化就是零初始化
    int i0{};
    long long i1{};
    double i2{};
    float i3{};
    char i4{};
    std::cout << "value initialize: " << std::endl;
    std::string fstr0 = std::format("{} {} {} {} '{}'", i0, i1, i2, i3, i4);
    std::cout << fstr0 << std::endl;

    i0 = 10;
    i1 = 10000;
    i2 = 100.11;
    i3 = 11.11;
    i4 = 'a';
    std::cout << "current value : " << std::endl;
    std::string fstr1 = std::format("{} {} {} {} '{}'", i0, i1, i2, i3, i4);
    std::cout << fstr1 << std::endl;

    // int i = new int(); 也是值初始化, 这里使用定位new是为了说明基本类型
    // 的值初始化相当于零初始化，变量所在的内存的值将会被零初始化
    int *p0 = new (&i0) int{};
    long long *p1 = new (&i1) long long{};
    double *p2 = new (&i2) double{};
    float *p3 = new (&i3) float{};
    char *p4 = new (&i4) char{};
    std::cout << "after value initialize: " << std::endl;
    std::string fstr2 = std::format("{} {} {} {} '{}'", *p0, *p1, *p2, *p3, *p4);
    std::cout << fstr2 << std::endl;

    return 0;
}
