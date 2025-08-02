#include <functional>

template <typename T, typename F = std::less<T>>
int compare(const T &v1, const T &v2, F f = F()) {
    if (f(v1, v2)) {
        return -1;
    } else if (f(v2, v1)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    compare(1, 2);

    return 0;
}
