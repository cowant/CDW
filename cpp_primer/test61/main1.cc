#include <iostream>
using namespace std;

// 第一个基类
class BaseA {
public:
    BaseA() { cout << "BaseA 构造" << endl; }
    ~BaseA() { cout << "BaseA 析构" << endl; }
    void taskA() { cout << "执行 A 的任务" << endl; }
};

// 第二个基类
class BaseB {
public:
    BaseB() { cout << "BaseB 构造" << endl; }
    ~BaseB() { cout << "BaseB 析构" << endl; }
    void taskB() { cout << "执行 B 的任务" << endl; }
};

// 多重继承语法：同时继承 BaseA 和 BaseB
class Derived : public BaseA, public BaseB {
public:
    Derived() { cout << "Derived 构造" << endl; }
    ~Derived() { cout << "Derived 析构" << endl; }
};

int main() {
    // 实例化子类对象
    Derived obj;

    // 子类可以调用所有父类的 public 成员
    obj.taskA();
    obj.taskB();

    return 0;
}
