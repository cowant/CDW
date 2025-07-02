#include <string>

template <typename T> using P1 = std::pair<T, T>;
template <typename T> using P2 = std::pair<T, std::string>;

int main () {
    P1<int> p1(1, 2);

    P2<int> p2(100, "hello");

    P2<double> p3(100.00, "hello");

    return 0;
}
