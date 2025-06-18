#include <vector>
#include <memory>
#include <initializer_list>

template <typename T>
class A {
public:
    A() = default;
    A(std::initializer_list<T> li) : data_(std::make_shared<std::vector<T>>(li)) {}

    size_t size() const;

private:
    std::shared_ptr<std::vector<T>> data_;
};

template <typename T>
inline size_t A<T>::size() const {
    return data_->size();
}
