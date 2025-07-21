#include <iostream>
#include <vector>

template <typename T>
typename T::value_type top(const T& c) {
    if (!c.empty()) {
        return c.back();
    } else {
        return typename T::value_type();
    }
}

int main() {
    std::vector<int> vec = {1, 2, 3, 5};

    std::cout << top(vec) << std::endl;

    return 0;
}
