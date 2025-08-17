#include <string>

template <typename T>
int Compare(const T& a, const T& b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

int main() {
    int (*func1) (const int&, const int &) = Compare;
    int (*func2) (const std::string&, const std::string&) = Compare;

    func1(1, 2);
    func2(std::string("a"), std::string("b"));

    return 0;
}
