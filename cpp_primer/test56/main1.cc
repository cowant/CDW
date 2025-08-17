#include <vector>
#include <type_traits>
#include <string>

template <typename Iter>
auto Func(Iter beg, Iter end) -> typename std::remove_reference<decltype(*beg)>::type {
    return *beg;
}

int main() {
    std::vector<std::string> vec = {"a", "b", "c", "d"};

    return 0;
}
