#include <iostream>

class A {
  public:
      A() {
          std::cout << "A::A(): object at " << this << " has value: " << a_ << std::endl;
      };

      explicit A(int a) : a_{a} {
          std::cout << "A::A(int): object at " << this << " has value: " << a_ << std::endl;
      }

      A(A rhs) {
          a_ = rhs.a_;
          std::cout << "A::A(A&): object at " << this << " has value: " << a_ << std::endl;
      }
  public:
      int a_{0};
};


int main() {
    A a1;

    A a2 = a1;

    return 0;
}
