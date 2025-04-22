#include "A.h"
#include "B.h"

int main() {
    A a(100, 200);

    a.Display();

    std::ostringstream oss;
    B b(oss);
    b.Serialize(a);

    b.Display();

    return 0;
}
