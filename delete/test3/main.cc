#include <iostream>


struct NoDtor {
    NoDtor() = default;
    ~NoDtor() = delete;

    NoDtor(const NoDtor&) = delete;
    NoDtor& operator=(const NoDtor&) = delete;
};

int main() {
    NoDtor o1;

    auto p = new NoDtor;

    return 0;
}
