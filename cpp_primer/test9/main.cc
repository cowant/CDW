#include <iostream>
#include <format>

class A;

void F1(A a);
void F2(A *p);
void F3(A &a) {}

A F4();
A* F5();
A& F6();

A F7(A a) {return a;}
A* F8() {return nullptr;}
A& F9(A &a) {return a;}

int main() {
    A *p = nullptr;
    A &a = *p;

    return 0;
}
