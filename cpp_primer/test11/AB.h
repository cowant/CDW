#ifndef _AB_H_
#define _AB_H_

#include <iostream>
#include <sstream>
#include <format>

class A;

class B {
public:
    B(std::ostringstream &out) : out_(out) {}
    void Display() const {
        std::cout << out_.str() << std::endl;
    }
    // 只有A的前向声明， 用A的引用作为形参，
    void Serialize(const A&);
private:
    std::ostringstream &out_;
};

class A {
// 这里声明了B::Serialize是A的友元，那么B的完整声明应该放在前面，不然就看不到
// B::Serialize这个符号了
friend void B::Serialize(const A&);
public:
    A() = default;
    A(int a, int b) : a_{a}, b_{b} {}

    void Display() const {
        std::string fstr = std::format("a: {} b{}", a_, b_);
        std::cout << fstr << std::endl;
    }
private:
    int a_{10};
    int b_{20};
};

void B::Serialize(const A& a) {
    out_ << "#" << "int:" << a.a_ << "#" << "int:" << a.b_;
}

#endif
