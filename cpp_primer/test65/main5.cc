#include <iostream>
#include <map>
#include <string>
#include <functional>

class Character {
public:
    // 1. 定义带参数的函数包装器：接收一个 int 类型的动态参数
    using DynamicAction = std::function<void(int)>;

    void attack(int p) { std::cout << "  [攻击] 造成了 " << p << " 点伤害！" << std::endl; }
    void heal(int p)   { std::cout << "  [治疗] 恢复了 " << p << " 点生命！" << std::endl; }

    void handleInput(const std::string& key, int currentPower) {
        // 2. 映射表：虽然函数在类里，但我们通过 Lambda 桥接
        // 注意：Lambda 的参数列表 (int p) 必须匹配 std::function 的声明
        static std::map<std::string, DynamicAction> actionMap = {
            {"J", [this](int p) { this->attack(p); }},
            {"H", [this](int p) { this->heal(p); }}
        };

        if (actionMap.count(key)) {
            // 3. 动态传参：在调用这一刻，才把 currentPower 传进去
            actionMap[key](currentPower); 
        }
    }
};

int main() {
    Character player;
    
    std::cout << "--- 动态参数系统 ---" << std::endl;
    
    // 场景 A：轻点按键，威力为 10
    player.handleInput("J", 10);
    
    // 场景 B：长按蓄力，威力为 100
    player.handleInput("J", 100);
    
    return 0;
}
