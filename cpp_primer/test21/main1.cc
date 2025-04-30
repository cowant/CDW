#include <iostream>

class Debug {
public:
    constexpr Debug() = default;
    constexpr Debug(bool b) : hw{b}, io{b}, other{b} {}
    constexpr Debug(bool h, bool i, bool o) : hw{h}, io{i}, other{o} {}

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
    bool hw = true;
    bool io = true;
    bool other = true;
};

int main() {
    constexpr Debug dbg0;
    constexpr Debug dbg1(false, true, false);
    constexpr Debug dbg2(true);

    return 0;
}
