#include <iostream>
#include <vector>


struct A {
    A() {
        std::cout << "A::A()" << std::endl;
    }
    A(const A&) {
        std::cout << "A::A(const A&)" << std::endl;
    }
    ~A() {
        std::cout << "A::~A()" << std::endl;
    }
};


int main() {
    std::vector<std::vector<A>> vecs;

    std::vector<A> vec{A(), A(), A()};
    vecs.emplace_back(std::move(vec));

    std::cout << "clearing..." << std::endl;
    vecs.clear();
    std::cout << "finished..." << std::endl;

    return 0;
}
