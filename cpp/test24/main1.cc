#include <iostream>
#include <string>
#include <memory>
#include <format>

class A {
public:
    A() = default;
    A(int a) : a_{a} {
        std::string fstr = std::format("constructing @ {}", static_cast<void *>(this));
        std::cout << fstr << std::endl;
    }

    ~A() {
        std::string fstr = std::format("destructing @ {}", static_cast<void *>(this));
        std::cout << fstr << std::endl;
    }

    void SetNext(std::shared_ptr<A> ptr) {
        next_ = ptr;
    }
private:
    int a_{0};
    std::shared_ptr<A> next_{nullptr};
};

int main() {
    auto a1 = std::make_shared<A>(1);
    auto a2 = std::make_shared<A>(2);

    a1->SetNext(a2);
    a2->SetNext(a1);

    return 0;
}
