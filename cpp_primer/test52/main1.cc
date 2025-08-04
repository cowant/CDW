#include <iostream>
#include <string>
#include <memory>

class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}
    template <typename T> void operator()(T *p) {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream &os;
};

int main() {
    std::unique_ptr<int, DebugDelete> p1(new int, DebugDelete());
    std::unique_ptr<std::string, DebugDelete> p2(new std::string, DebugDelete());

    return 0;
}
