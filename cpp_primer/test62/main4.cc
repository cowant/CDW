#include <iostream>
#include <new>      // 必须包含此头文件

class MyClass {
public:
    MyClass(int v) : value(v) { std::cout << "Constructor: " << value << "\n"; }
    ~MyClass() { std::cout << "Destructor: " << value << "\n"; }
private:
    int value;
};

int main() {
    // 1. 预分配一块足以容纳对象的内存（例如在栈上）
    char buffer[sizeof(MyClass)];

    // 2. 使用定位 new 在 buffer 地址上构造对象
    // 注意：这里没有分配新内存，只是初始化了 buffer 所在的内存
    MyClass* obj = new (buffer) MyClass(42); 

    // 3. 关键：禁止对 obj 使用 delete！
    // 因为内存不是由 new 分配的，调用 delete 会尝试释放栈内存，导致程序崩溃。
    // delete obj; // 错误！

    // 4. 手动调用析构函数来销毁对象
    obj->~MyClass();

    return 0;
}
