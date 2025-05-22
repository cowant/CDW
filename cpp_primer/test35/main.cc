#include <iostream>
#include <string>
#include <format>

class A {
public:
    A() = default;
    A(int a, int b) : a_{a}, b_{b} {}
    virtual ~A() = default;

protected:
    int a_{10};
    int b_{20};
};

class B : public A {
friend std::ostream& operator<<(std::ostream &out, const B& b);
public:
    B() = default;
    explicit B(int c) : A(), c_{c} {}
    ~B() = default;

    void Display() const {
        std::string fstr = std::format("{} {} {}", a_, b_, c_);
        std::cout << fstr << std::endl;
    }
private:
    int c_{30};
};

std::ostream& operator<<(std::ostream &out, const B& b) {
    std::string fstr = std::format("{} {} {}", b.a_, b.b_, b.c_);
    out << fstr;
    return out;
}

int main() {
    B b(40);
    b.Display();

    std::cout << b << std::endl;

    return 0;
}
