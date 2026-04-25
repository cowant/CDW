#include <iostream>
#include <variant> // 引入头文件
#include <string>

int main() {
    // 1. 定义：表示这个变量可以是 int 或 std::string
    std::variant<int, std::string> data;

    // 2. 赋值：直接赋 int
    data = 42;
    std::cout << "整数: " << std::get<int>(data) << std::endl;

    // 3. 切换：直接赋 string，它会自动销毁之前的 int 并构造 string
    data = "Hello, Modern C++!";
    std::cout << "字符串: " << std::get<std::string>(data) << std::endl;

    // 4. 安全检查：如果存的是 string 你非要取 int，它会抛出异常
    try {
        int val = std::get<int>(data);
    } catch (const std::bad_variant_access& e) {
        std::cout << "报错了: " << e.what() << " (类型不匹配！)" << std::endl;
    }

    return 0; // 自动清理内存，绝无泄漏
}
