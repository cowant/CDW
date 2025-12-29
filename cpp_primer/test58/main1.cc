#include <string>
#include <utility>

int main() {
    std::string s1("xxxx"), s2;

    s2 = std::move(std::string("zzzz")); // 正确，从一个右值移动数据
    s2 = std::move(s1); // 正确，但在赋值之后，s1的值是不确定的

    return 0;
}
