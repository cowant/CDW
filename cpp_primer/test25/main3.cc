#include <iostream>

class A {
  public:
      A() {
          std::cout << "A::A(): object at " << this << " has value: " << a_ << std::endl;
      };

      explicit A(int a) : a_{a} {
          std::cout << "A::A(int): object at " << this << " has value: " << a_ << std::endl;
      }

      ~A() {
          std::cout << "A::~A(): object at " << this << " has value: " << a_ << std::endl;
      };

      A(A& rhs) : a_{rhs.a_} {
          std::printf("A::A(A&): {lhs : rhs} <==> {%p : %p}\n", this, &rhs);
      }

  public:
      int a_{0};
};


A Func(int i) {
    A a(i * i);
    return a;
}

int main() {
    A a = Func(10);
    std::cout << "a @" << &a << std::endl;

    return 0;
}
