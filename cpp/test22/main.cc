#include <iostream>
#include <string>

struct foo {
    void bar();
    static constexpr char baz[] = "quz";
};

void foo::bar() {
    std::string str(baz);
    std::cout << str << std::endl;
}

int main() {
    foo f;

    f.bar();

    return 0;
}
