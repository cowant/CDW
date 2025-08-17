#include <string>
#include <iostream>
#include <utility>

template <typename T>
void Func(T&& a) {
    T i = 5;
}

int main() {
    int i = 0;
    Func(i);
    Func(5);

    return 0;
}
