#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    string name;
    // 带有参数的构造函数
    Animal(string n) : name(n) { 
        cout << "1. Animal 构造函数被调用，名字是: " << name << endl; 
    }
    virtual ~Animal() {
        cout << "1. Animal 析构函数被调用，名字是: " << name << endl; 
    }
};

// 中间层必须使用 virtual 继承
class Mammal : virtual public Animal {
public:
    // 尽管这里写了初始化 Animal，但在虚继承下会被底层的 Bat 忽略
    Mammal() : Animal("Default Mammal") { 
        cout << "2. Mammal 构造函数被调用" << endl; 
    }
    virtual ~Mammal() {
        cout << "2. Mammal 析构函数被调用" << endl; 
    }
};

class Bird : virtual public Animal {
public:
    Bird() : Animal("Default Bird") { 
        cout << "3. Bird 构造函数被调用" << endl; 
    }
    virtual ~Bird() {
        cout << "3. Bird 析构函数被调用" << endl; 
    }
};

// 最底层类
class Bat : public Mammal, public Bird {
public:
    // 关键点：Bat 必须直接在初始化列表中调用 Animal 的构造函数
    Bat() : Animal("我是唯一的蝙蝠"), Mammal(), Bird() {
        cout << "4. Bat 构造函数被调用" << endl;
    }
    ~Bat() {
        cout << "4. Bat 析构函数被调用" << endl;
    }
};

int main() {
    cout << "--- 开始创建 Bat 对象 ---" << endl;
    Bat myBat;
    
    cout << "\n最终的名字是: " << myBat.name << endl;
    return 0;
}
