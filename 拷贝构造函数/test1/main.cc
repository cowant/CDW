#include <iostream>

class A {
  public:
      A() {
          std::cout << "A::A(): object at " << this << " has value: " << a_ << std::endl;
      };

      explicit A(int a) : a_{a} {
          std::cout << "A::A(int): object at " << this << " has value: " << a_ << std::endl;
      }

      A(const A& rhs) {
          a_ = rhs.a_;
          std::cout << "A::A(A&): object at " << this << " has value: " << a_ << std::endl;
      }

      void Display() const {
        std::cout << a_ << std::endl;
      }

  public:
      int a_{0};
};


void Func1(A a) {
    // do nothing
}

A Func2(int i) {
    A a(i * i);
    return a;
}

struct B {
    double d_;
    A a_;
};

int main() {
    A a1;

    std::cout << std::endl << "case: 1)"  << std::endl;
    A a2 = a1;

    // 形参类型为非引用类型
    std::cout << std::endl << "case: 2)"  << std::endl;
    Func1(a1);

    // 返回类型为非引用类型
    std::cout << std::endl << "case: 3)"  << std::endl;
    A a3 = Func2(10);

    // 数组列表初始化
    std::cout << std::endl << "case: 4)"  << std::endl;
    A arr[2] = {a1, a1};

    // 聚合类列表初始化
    std::cout << std::endl << "case: 5)"  << std::endl;
    B b{1.1, a1};


    return 0;
}
