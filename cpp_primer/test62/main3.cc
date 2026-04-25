#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

class tracker {
public:
    tracker() {
        std::cout << "  [Step 2] Constructor: I'm going to throw an exception now...\n";
        throw std::runtime_error("Construction Failed!");
    }

    // 自定义带参数的 new
    void* operator new(size_t size, const std::string& tag) {
        std::cout << "  [Step 1] Custom new: Allocating " << size << " bytes for [" << tag << "]\n";
        return std::malloc(size);
    }

    // 标准 delete (手动 delete 时调用)
    void operator delete(void* p) {
        std::cout << "  [Step 3?] Standard delete called.\n";
        std::free(p);
    }

    // 与自定义 new 签名匹配的 placement delete
    // 仅在构造函数抛出异常时由编译器自动触发
    void operator delete(void* p, const std::string& tag) {
        std::cout << "  [Step 3] Matching delete: Cleaning up [" << tag << "] due to exception.\n";
        std::free(p);
    }
};

int main() {
    std::cout << "Starting Test...\n";
    try {
        // 尝试创建一个对象
        tracker* ptr = new ("MySecretData") tracker();
    } catch (const std::exception& e) {
        std::cout << "Caught Exception: " << e.what() << "\n";
    }
    
    std::cout << "Test Finished.\n";
    return 0;
}
