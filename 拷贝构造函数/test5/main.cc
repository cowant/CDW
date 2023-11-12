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
          std::cout << "A::A(const A&): object at " << this << " has value: " << a_ << std::endl;
      }
  public:
      int a_{0};
};


int main() {
    A a1{10};

    // 正确，直接初始化，由用户显式调用拷贝构造函数
    A a2(a1);

    // 这里我们先显式构造一个临时对象A(a2)，这是没有问题的，然后用这个临时对象隐式
    // 调用拷贝构造函数。按道理来说是不行的，所以即使我们使用elide constructor优化
    // 那么对于-std=C++11, 还是会编译报错，因为此时编译器需要检查这个拷贝构造函数是
    // 可用的，但显然它是explicit的，并不可用。
    //
    // 而对于-std=c++17或者-std=c++20，这种写法并没有问题，也就是c++17和c++20强制使用
    // elide constructor, 而不管拷贝构造函数此时是否是explicit。
    A a3 = A(a2);

    return 0;
}
