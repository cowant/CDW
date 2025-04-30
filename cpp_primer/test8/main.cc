#include <iostream>
#include <format>

class A {
public:
    A() = default;
    A(int a, int b) : a_{a}, b_{b} {}

    void Display() const {
        std::cout << "from const member function: " << std::endl;
        DoDisplay();
    }

    void Display() {
        std::cout << "from non-const member function: " << std::endl;
        DoDisplay();
    }
private:
    void DoDisplay()  const {
        std::string fstr = std::format("{} {} {} a: {}, b: {}", __FILE__, __LINE__, __func__, a_, b_);
        std::cout << fstr << std::endl;
    }

    int a_{1};
    int b_{2};
};
int main() {
    const A a(10, 20);
    A b(100, 200);

    a.Display();
    b.Display();

    return 0;
}
