#include <iostream>
#include <memory>
#include <string>
#include <format>
#include <vector>

class A {
public:
    A() {
        std::string fstr = std::format("constructing {}", static_cast<void*>(this));
        std::cout << fstr << std::endl;
    }

    A(int a) : a_{a} {
        std::string fstr = std::format("constructing @{} with {}", static_cast<void*>(this), a);
        std::cout << fstr << std::endl;
    }
    ~A() {
        std::string fstr = std::format("destructing @{}", static_cast<void*>(this));
        std::cout << fstr << std::endl;
    }
private:
    int a_{0};
};

int main() {
    auto p1 = std::make_shared<A>(1);
    auto p2 = std::make_shared<A>(2);
    auto p3 = std::make_shared<A>(3);
    auto p4 = std::make_shared<A>(4);

    std::vector<std::shared_ptr<A>> ptrs = {p1, p2, p3, p4};

    return 0;
}
