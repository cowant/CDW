#include <iostream>

namespace MyLib {
    // 旧版本定义在普通命名空间
    namespace V1 {
        void func() {
            /* 旧版本逻辑 */
            std::cout << "V1" << std::endl;
        }
    }

    // 新版本定义为 inline namespace
    inline namespace V2 {
        void func() {
            /* 新版本优化后的逻辑 */
            std::cout << "V2" << std::endl;
        }
    }
}

int main() {
    // 1. 默认调用：直接通过 MyLib 访问，会自动找到 V2 (inline)
    MyLib::func(); 

    // 2. 显式调用旧版：如果用户还没适配新逻辑，可以手动指定 V1
    MyLib::V1::func();

    // 3. 显式调用新版：也可以写全称，但通常没必要
    MyLib::V2::func(); 

    return 0;
}
