#include "common.h"
#include <iostream>
#include <format>

inline void A::Display() const {
    std::string fstr = std::format("{} {} {}", __FILE__, __LINE__, __func__);
    std::cout << fstr << std::endl;
}

void A::Display2() const {
    Display();
}
