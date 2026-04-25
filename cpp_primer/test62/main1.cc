#include <iostream>
#include <cstdlib>

class MyClass {
public:
    int data;

    // 重载类成员 operator new
    void* operator new(size_t size) {
        std::cout << "Custom new: Allocating " << size << " bytes." << std::endl;
        void* p = std::malloc(size); // 实际分配内存
        if (!p) throw std::bad_alloc();
        return p;
    }

    // 重载类成员 operator delete
    void operator delete(void* p) noexcept {
        std::cout << "Custom delete: Freeing memory." << std::endl;
        std::free(p); // 实际释放内存
    }
};

int main() {
    MyClass* obj = new MyClass(); // 调用自定义 operator new
    delete obj;                  // 调用自定义 operator delete
    return 0;
}
