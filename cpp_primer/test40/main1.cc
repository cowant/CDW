#include <iostream>

class B {
public:
    B() = default;
    B(int a) : a_{a} {}
    virtual ~B() = default;

    B(const B& rhs) : a_{rhs.a_} {
        std::cout << "copy contructor of B" << std::endl;
    }

    B(B&& rhs) : a_{rhs.a_} {
        std::cout << "move contructor of B" << std::endl;
    }
private:
    int a_{0};
};

class D : public B {
public:
    D() = default;
    D(int a, int b) : B(a), b_{b} {}
    ~D() = default;

    D(const D &rhs) : B(rhs), b_{rhs.b_}{
        std::cout << "copy contructor of D" << std::endl;
    }

    D(D &&rhs) : B(std::move(rhs)), b_{rhs.b_}{
        std::cout << "move contructor of D" << std::endl;
    }
private:
    int b_{100};
};

int main () {
    D d1(10, 20);

    D d2 = d1;
    D d3 = std::move(d2);

    return 0;
}
