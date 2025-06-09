#include <iostream>

class B {
public:
    B() = default;
    B(int a) : a_{a} {}

    B(const B& rhs) : a_{rhs.a_} {
        std::cout << "copy contructor of B" << std::endl;
    }

    B(B&& rhs) : a_{rhs.a_} {
        std::cout << "move contructor of B" << std::endl;
    }
private:
    int a_{0};
};

class X1 {
public:
    X1() = default;
    ~X1() = default;
private:
    B b_{10};
};

class X2 {
public:
    X2() = default;
private:
    B b_{10};
};

int main () {
    X1 x1;
    X2 x2;

    X1 xx1 = std::move(x1);
    std::cout << "###" << std::endl;
    X2 xx2 = std::move(x2);

    return 0;
}
