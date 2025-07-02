#include <iostream>

template <typename T>
class Foo {
public:
    Foo() = default;
    static std::size_t Count() {
        std::cout << "address @" << &cnt << std::endl;
        return cnt;
    }
private:
    static std::size_t cnt;
};

template <typename T> std::size_t Foo<T>::cnt = 0;

int main() {
    Foo<std::string> f1;
    Foo<std::string> f2;
    Foo<int> f3;
    Foo<int> f4;

    f1.Count();
    f2.Count();
    f3.Count();
    f4.Count();

    return 0;
}
