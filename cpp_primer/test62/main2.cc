#include <iostream>
#include <string>
#include <cstdlib>

class MyObject {
public:
    // 1. 标准重载 (不带自定义参数)
    void* operator new(size_t size) {
        std::cout << "[Standard New] Size: " << size << " bytes" << std::endl;
        return std::malloc(size);
    }

    // 2. 带自定义参数的重载 (用于追踪)
    // 第一个参数必须是 size_t，后续为自定义参数
    void* operator new(size_t size, const std::string& tag, int line) {
        std::cout << "[Custom New] Tag: " << tag 
                  << " | Line: " << line 
                  << " | Size: " << size << " bytes" << std::endl;
        return std::malloc(4);
    }

    // 3. 必须配套的标准 delete
    void operator delete(void* p) {
        std::cout << "[Standard Delete] Freeing memory" << std::endl;
        std::free(p);
    }

    // 4. 配套的带参数 delete (Placement Delete)
    // 注意：只有当构造函数抛出异常时，编译器才会自动调用这个版本的 delete
    void operator delete(void* p, const std::string& tag, int line) {
        std::cout << "[Custom Delete Cleanup] Exception during construction of " << tag << std::endl;
        std::free(p);
    }

private:
    int id = 0;
};

int main() {
    // 调用标准 new
    std::cout << "--- Test 1 ---" << std::endl;
    MyObject* obj1 = new MyObject();
    delete obj1;

    // 调用带参数的 custom new
    // 语法：new (额外参数) 类型(构造函数参数)
    std::cout << "\n--- Test 2 ---" << std::endl;
    MyObject* obj2 = new ("NetworkModule", 102) MyObject();
    delete obj2; // 注意：显式 delete 依然调用标准 operator delete

    return 0;
}
