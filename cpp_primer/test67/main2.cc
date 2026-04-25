#include <iostream>
#include <string>

struct CustomData {
    // 1. 定义标签来跟踪活跃成员
    enum Type {
        INT,
        STRING
    } type;

    // 2. 包含 string 的匿名 union
    union {
        int i;
        std::string s; // 非平凡成员（有自己的内存管理）
    };

    // 3. 构造函数：默认初始化为 int
    CustomData() : type(INT), i(0) {}

    // 4. 析构函数：必须手动销毁活跃状态的 string
    ~CustomData() {
        if (type == STRING) {
            using std::string; // using指示非常重要
            s.~string(); // 显式调用析构函数，释放 string 内部堆空间
        }
    }

    // 切换到 String 模式的辅助函数
    void setString(const std::string& str) {
        if (type == STRING) {
            s = str; // 已经是 string，直接赋值
        } else {
            // 关键步骤：使用 placement new 在既有内存上构造 string 对象
            new (&s) std::string(str); 
            type = STRING;
        }
    }

    // 切换到 Int 模式的辅助函数
    void setInt(int val) {
        if (type == STRING) {
            using std::string; // using指示非常重要
            s.~string(); // 覆盖内存前，必须先销毁旧的 string 避免内存泄漏
        }
        i = val;
        type = INT;
    }
};

int main() {
    CustomData data;

    data.setInt(42);
    std::cout << "整数模式: " << data.i << std::endl;

    data.setString("Hello, C++ Union!");
    std::cout << "字符串模式: " << data.s << std::endl;

    // 离开作用域时，析构函数会自动清理字符串
    return 0; 
}
