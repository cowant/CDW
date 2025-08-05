#ifndef _bigfunction_h_
#define _bigfunction_h_

#include <string>

template <typename T>
void BigFunction() {
    ; // do nothing
}

extern template void BigFunction<int>();
extern template void BigFunction<std::string>();

#endif
