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

      A(const A& rhs) : a_{rhs.a_} {
          std::printf("A::A(const A&): {lhs : rhs} <==> {%p : %p}\n", this, &rhs);
      }

      A(A&&) = delete;


  public:
      int a_{0};
};

A Func(int i) {
    A a(i * i);

    return a;
}

int main() {
    Func(10);

    return 0;
}
