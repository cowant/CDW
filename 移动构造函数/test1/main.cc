#include <stdio.h>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> s;

    // 调用右值引用版本
    s.push_back("xxxx");
    return 0;
}
