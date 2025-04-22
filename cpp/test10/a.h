#ifndef _A_H_
#define _A_H_

#include <iostream>
#include <format>

class A {
public:
    friend void Display(const A &a) {
        std::string fstr = std::format("a: {} b: {}", a.a_, a.b_);
        std::cout << fstr << std::endl;
    }
    A() = default;
    A(int a, int b) : a_{a}, b_{b} {}
private:
    int a_{10};
    int b_{20};
};

//
// 友元声明仅仅指定了访问的权限，而非一个通常意义上的函数声明。如果我们希望类的用户
// 能够调用某个友元函数，那么我们就必须在友元声明之外再专门对函数进行一次声明。
//
// 为了使友元对类的用户可见，我们通常把友元的声明与类本身放置在头一个头文件中(类的外部)。
//
// 一些编译器允许在尚无友元函数的初始声明的情况下就调用它。不过即使你的编译器支持这种
// 行为，最好还是提供一个独立的函数声明，这样即使你更换了一个有这种强制要求的编译器，
// 也不必改变代码
void Display(const A &a);

#endif
