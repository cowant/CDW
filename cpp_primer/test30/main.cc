#include <iostream>
using namespace std;

class A {
public:
    void action() {
        cout << "Action in class A!" << endl;
    }
};

class B {
public:
    A* operator->() {
        return &a;
    }
    void action() {
        cout << "Action in class B!" << endl;
    }
private:
    A a;
};

class C {
public:
    B operator->() {
        return b;
    }
    void action() {
        cout << "Action in class C!" << endl;
    }
private:
    B b;
};


int main() {
    C* pc = new C;
    pc->action();

    C c;
    c->action();

    return 0;
}
