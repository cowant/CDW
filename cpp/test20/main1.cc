#include <iostream>
#include <string>
#include <vector>

class A {
public:
    A() {
        std::cout << "default contructing" << std::endl;
    }
    A(int a) : a_{a} {
        std::cout << "contructing with " << a << std::endl;
    }

    A(const A& a) : a_{a.a_} {
        std::cout << "copy contructing with " << a_ << std::endl;
    }
private:
    int a_{0};
};

struct B {
    std::string s_{"hello, world"};
    A a_;
    std::vector<A> b_;
};

int main () {
    A a1{1};
    A a2{2};
    A a3{3};

    std::cout << "b1: " << std::endl;
    B b1 = {"xxx", 10, {a1, a2, a3}};

    std::cout << "b2: " << std::endl;

    // 初始化列表没有给B::a_和B::b_成员提供初始值，它们将执行值初始化，
    B b2 = {"xxx"};
    return 0;
}
