#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class A {
public:
    A() = default;
    A(std::initializer_list<T> li) : data_(li) {}

    size_t size() const {
        return data_.size();
    }

    A& X2() {
        for (auto &d : data_) {
            d *= 2;
        }
        return *this;
    }

    A& X3();

    void Display() const {
        for (const auto &d : data_) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> data_;
};

template <typename T>
A<T>& A<T>::X3() {
    for (auto &d : data_) {
        d *= 3;
    }

    A& ret = *this;
    return ret;
}
