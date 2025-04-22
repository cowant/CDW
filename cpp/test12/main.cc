#include "A.h"
#include "B.h"

int main() {
    A a(200, "XXXX");
    std::cout << a << std::endl;

    B b(300, "ZZZZ");
    std::cout << b << std::endl;

    b.CopyFrom(a);
    std::cout << b << std::endl;

    return 0;
}
