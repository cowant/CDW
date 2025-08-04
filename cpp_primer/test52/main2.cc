#include <iostream>
#include <list>
#include <vector>

template <typename T>
class A {
public:
    template <typename It> A(It b, It e);
private:
    std::vector<T> data;
};

template <typename T>
template <typename It>
A<T>::A(It b, It e) : data(b, e) {
    std::cout << "template constructor" << std::endl;
}

int main() {
    std::list<int> list2 = {1, 2, 3};
    A<int> a(list2.begin(), list2.end());

    return 0;
}
