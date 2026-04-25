#include <iostream>
#include <map>
#include <string>
#include <functional>

// 导入占位符命名空间，方便使用 _1, _2
using namespace std::placeholders;

class Character {
public:
    using DynamicAction = std::function<void(int)>;

    void attack(int p) { std::cout << "  [攻击] 威力: " << p << std::endl; }
    void heal(int p)   { std::cout << "  [治疗] 恢复: " << p << std::endl; }

    void handleInput(const std::string& key, int power) {
        // 使用 std::bind 简化 Lambda
        // std::bind(函数地址, 实例指针, 参数占位符)
        static std::map<std::string, DynamicAction> actionMap = {
            {"J", std::bind(&Character::attack, this, _1)},
            {"H", std::bind(&Character::heal, this, _1)}
        };

        if (actionMap.count(key)) {
            actionMap[key](power); // 这里的 power 会填充到 _1 的位置
        }
    }
};

int main() {
    Character player;
    player.handleInput("J", 50);
    player.handleInput("H", 30);
    return 0;
}
