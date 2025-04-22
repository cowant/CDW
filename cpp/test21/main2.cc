#include <iostream>

class Debug {
public:
    constexpr Debug(bool b) : hw{b}, io{b} {}

    constexpr bool any() const {
        return hw || io || other;
    }

    void set_hw(bool b) {
        hw = b;
    }

    void set_io(bool b) {
        io = b;
    }

    void set_other(bool b) {
        other = b;
    }
private:
    bool hw;
    bool io;
    bool other;
};

int main() {
    constexpr Debug dbg1(true);

    return 0;
}
