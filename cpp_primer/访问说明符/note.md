# 访问说明符

类派生列表的形式是：首先是一个冒号，后面紧跟以逗号分隔的基类列表，其中每个基类前面可以有以下三种访问说明符中的一种：

- public
- protected
- private

访问说明符的作用是控制派生类从基类继承而来的成员是否对派生类的用户可见。


如果一个派生类是公有的，则基类的公有成员也是派生类接口的组成部分。此外，我们能将公有派生类型的对象绑定到基类的引用或指针上。因为我们在派生列表中使用了public访问说明符。

```cpp
// test1
#include <iostream>

class B {

};

class D : protected B {

};

int main() {
    D d;

    B& b = d;

    return 0;
}
```

在这个例子中，我们使用了protected访问说明符，那么基类对于派生类的用户而言就是不可见的。如果派生类对象可以绑定到基类的引用上，那就意味着我们通过这个引用可以访问到派生类中的基类部分，这就失去了protected的保护作用。所以编译器会阻止这种绑定。

```bash
$ g++ main.cc
main.cc: In function ‘int main()’:
main.cc:14:12: error: ‘B’ is an inaccessible base of ‘D’
   14 |     B& b = d;
      |            ^
```