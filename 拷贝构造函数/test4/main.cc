#include <iostream>

class A {
  public:
      A() {
          std::cout << "A::A(): object at " << this << " has value: " << a_ << std::endl;
      };

      explicit A(int a) : a_{a} {
          std::cout << "A::A(int): object at " << this << " has value: " << a_ << std::endl;
      }

      explicit A(const A& rhs) {
          a_ = rhs.a_;
          std::cout << "A::A(A&): object at " << this << " has value: " << a_ << std::endl;
      }
  public:
      int a_{0};
};

void F(A a) {
    std::cout << "xxx" << std::endl;
}


int main() {
    A a1{10};

    // 正确，直接初始化，由用户显式调用拷贝构造函数
    A a2(a1);

    // 错误，拷贝初始化，它要求编译器隐式调用拷贝构造函数，但
    // 我们已经将拷贝构造函数声明为explicit的，所以编译器不能
    // 隐式调用它，那么在函数决议时就找不到可用函数，于是调用
    // 失败
    A a3 = a2;
    F(a2);

    return 0;
}
