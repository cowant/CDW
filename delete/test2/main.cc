#include <iostream>


struct NoCopy {
    NoCopy() = default;
    ~NoCopy() = default;

    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

int main() {
    NoCopy o1;

    NoCopy o2(o1);

    return 0;
}
