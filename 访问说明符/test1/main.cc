#include <iostream>

class B {

};

class D : protected B {

};

int main() {
    D d;

    B& b = d;

    return 0;
}
