# 派生类构造函数

派生类对象不能直接初始化基类的成员。尽管从语法上来说我们可以在**派生类构造函数体内**给它的公有或受保护的基类成员赋值，但是最好不要这么做。和使用基类的其他场合一样，派生类应该遵循基类的接口，并且**通过基类的构造函数来初始化那些从基类继承而来的成员**。


```cpp
// test1
#include <iostream>

struct B {
    int a_{0};
};

struct D : B {
    D(int a, const std::string &s) : a_{a}, name_{s} {}
    std::string name_;
};

int main() {
    D d(12, "hello");

    return 0;
}
```

如果通过派生类列表直接初始化基类的成员，编译会报错：
```bash
$ g++ main.cc
main.cc: In constructor ‘D::D(int, const string&)’:
main.cc:8:38: error: class ‘D’ does not have any field named ‘a_’
    8 |     D(int a, const std::string &s) : a_{a}, name_{s} {}
      |                                      ^~
```