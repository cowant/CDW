#include <iostream>
#include <vector>
#include <initializer_list>


template <typename> class A;
template <typename T> std::ostream& operator<<(std::ostream& out, const A<T> &a);

template <typename T>
class A {
friend std::ostream& operator<<<T>(std::ostream& out, const A &a);
public:
    A() = default;
    A(std::initializer_list<T> li) : data_(li) {}

    size_t size() const {
        return data_.size();
    }

private:
    std::vector<T> data_;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const A<T> &a) {
    for (const auto & e : a.data_) {
        out << e << " ";
    }

   return out;
}
