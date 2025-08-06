#include "template.hpp"

int main() {
    int a[12] = {};
    int b[12] = {};
    int c[42] = {};

    Fobj(a, b); // 调用Fobj(int *, int *)
    Fref(a, b); // 调用Fref(const int &[12], const inst &[12])
    Fref(b, c); // 错误，数组类型不匹配

    return 0;
}
