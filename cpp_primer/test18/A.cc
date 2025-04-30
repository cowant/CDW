#include <iostream>
#include <format>
#include <array>

int main() {
    // int i; 执行默认初始化，对于基本类型，默认类型就是啥也不做
    int i0;
    long long i1;
    double i2;
    float i3;
    char i4;
    std::cout << "default initialize: " << std::endl;
    std::string fstr0 = std::format("{} {} {} {} {}", i0, i1, i2, i3, i4);
    std::cout << fstr0 << std::endl;

    // int i = new int; 也是默认初始化, 这里使用定位new是为了说明基本类型
    // 的默认初始化相当于啥也不做，变量所在的内存当前所存的值是一个垃圾值
    int *p0 = new (&i0) int;
    long long *p1 = new (&i1) long long;
    double *p2 = new (&i2) double;
    float *p3 = new (&i3) float;
    char *p4 = new (&i4) char;
    std::cout << "default initialize: " << std::endl;
    std::string fstr1 = std::format("{} {} {} {} {}", *p0, *p1, *p2, *p3, *p4);
    std::cout << fstr1 << std::endl;

    return 0;
}
