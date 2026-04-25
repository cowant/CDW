#include <iostream>
#include <map>
#include <string>

class Character {
public:
    // 1. 定义成员函数指针类型
    // 语法：返回类型 (类名::*类型名)(参数列表)
    using ActionPtr =  void (Character::*)();

    void attack() { std::cout << "Character: 执行 [普通攻击]！" << std::endl; }
    void defend() { std::cout << "Character: 执行 [防御姿态]！" << std::endl; }
    void jump()   { std::cout << "Character: 执行 [英勇跳跃]！" << std::endl; }

    // 2. 模拟游戏主循环：根据输入执行动作
    void handleInput(const std::string& key) {
        // 创建一个“动作映射表” (Action Map)
        // 将按键字符串直接映射到对应的类成员函数
        static std::map<std::string, ActionPtr> actionMap = {
            {"J", &Character::attack},
            {"K", &Character::defend},
            {"Space", &Character::jump}
        };

        // 查找按键是否存在于表中
        if (actionMap.count(key)) {
            ActionPtr action = actionMap[key];
            // 3. 动态调用：通过成员函数指针执行动作
            // 注意：必须作用于当前对象 (*this)
            (this->*action)(); 
        } else {
            std::cout << "未定义的按键: " << key << std::endl;
        }
    }
};

int main() {
    Character player;

    std::cout << "--- 模拟玩家操作 ---" << std::endl;
    player.handleInput("J");     // 触发攻击
    player.handleInput("Space"); // 触发跳跃
    player.handleInput("W");     // 无效输入

    return 0;
}
