#include <iostream>
#include <string>
using namespace std;

class BaseA {
public:
    BaseA(int x) { cout << "BaseA 有参构造: " << x << endl; }
    BaseA() { cout << "BaseA 默认构造" << endl; }
};

class BaseB {
public:
    BaseB(string s) { cout << "BaseB 有参构造: " << s << endl; }
    BaseB() { cout << "BaseB 默认构造" << endl; }
};

class Derived : public BaseA, public BaseB {
public:
    // 使用 using 继承两个父类的构造函数
    using BaseA::BaseA;
    using BaseB::BaseB;

    // 子类新增成员（建议直接在这里给初始值，因为继承的构造函数不会管它）
    int myData = 0; 
};

int main() {
    cout << "--- 调用 BaseA 的继承构造函数 ---" << endl;
    // 此时会：1. 调用 BaseA(10)  2. 调用 BaseB() 默认构造
    Derived d1(10); 

    cout << "\n--- 调用 BaseB 的继承构造函数 ---" << endl;
    // 此时会：1. 调用 BaseA() 默认构造  2. 调用 BaseB("Hello")
    Derived d2("Hello");

    cout << "\n--- 调用合成的默认构造函数 ---" << endl;
    Derived d3;

    return 0;
}
