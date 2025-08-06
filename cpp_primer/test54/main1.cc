#include "template.hpp"
#include <string>

int main() {
    std::string s1("xxx");
    const std::string s2("zzz");

    Fobj(s1, s2); // 调用Fobj(std::string, std::string), s2的顶层const属性被忽略
    Fref(s1, s2); // 调用Fref(const std::string &, const std::string &)

    return 0;
}
