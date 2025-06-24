#include <vector>
#include <initializer_list>
#include <memory>


template <typename T> class B;

template <typename T>
class A {
friend class B<T>;
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
class B {
public:
    B() = default;
    B(std::shared_ptr<A<T>> ptr) : ptr_{ptr} {}

    void Clear(size_t i) {
        if (auto p = ptr_.lock()) {
           p->data_[i] = T();
        }
    }

private:
    std::weak_ptr<A<T>> ptr_;
};
