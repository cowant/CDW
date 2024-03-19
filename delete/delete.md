# delete

delete可以用于声明成员函数和非成员函数，它表示我们希望在代码中明确禁止这个函数所能实现的操作。


## 引导函数重载决议

```cpp
// test1
#include <iostream>

// 定义重载的Foo函数

void Foo(int) = delete;

void Foo(double) {
    std::cout << "Foo(double)" << std::endl;
}

int main() {
    Foo(10.0);

    // 重载决议将会匹配到void Foo(int) 版本
    Foo('c');
    Foo(true);

    return 0;
}
```

编译报错：
```bash
$ g++ main.cc
main.cc: In function ‘int main()’:
main.cc:15:8: error: use of deleted function ‘void Foo(int)’
   15 |     Foo('c');
      |     ~~~^~~~~
main.cc:5:6: note: declared here
    5 | void Foo(int) = delete;
      |      ^~~
main.cc:16:8: error: use of deleted function ‘void Foo(int)’
   16 |     Foo(true);
      |     ~~~^~~~~~
main.cc:5:6: note: declared here
    5 | void Foo(int) = delete;
      |      ^~~
```

可以看到delete的函数也在重载函数决议的候选集合中，并且因为是更好的匹配选择了void Foo(int)版本，但因为我们禁止这样的操作，导致了编译报错，这样给代码提供了更严格的类型检查。所以如果我们希望用户明确的传入double类型的参数来调用void Foo(double)，就可以将void Foo(int) 定义为删除的。

## 阻止拷贝

可以通过将拷贝构造函数和拷贝赋值运算符定义为删除的函数来阻止拷贝。比如iostream类不需要拷贝构造函数和拷贝赋值运算符。

```cpp
// test2
#include <iostream>

struct NoCopy {
    NoCopy() = default;
    ~NoCopy() = default;

    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

int main() {
    NoCopy o1;

    NoCopy o2(o1);

    return 0;
}
```

编译报错：

```bash
$ g++ main.cc
main.cc: In function ‘int main()’:
main.cc:15:17: error: use of deleted function ‘NoCopy::NoCopy(const NoCopy&)’
   15 |     NoCopy o2(o1);
      |                 ^
main.cc:8:5: note: declared here
    8 |     NoCopy(const NoCopy&) = delete;
      |     ^~~~~~
```

## 删除的析构函数

将析构函数定义为delete并没有什么语法错误，只是这样的一个对象在销毁时会调用析构函数，而这个析构函数又是delete的，编译器不会让我们调用它，于是就报错了，那么是不是说只要不销毁这个对象就可以了呢？确实，所以我们可以new一个这样的对象，但又不delete它。

```cpp
// test3
#include <iostream>

struct NoDtor {
    NoDtor() = default;
    ~NoDtor() = delete;

    NoDtor(const NoDtor&) = delete;
    NoDtor& operator=(const NoDtor&) = delete;
};

int main() {
    NoDtor o1;

    auto p = new NoDtor;

    return 0;
}
```

编译报错：

```bash
$ g++ main.cc
main.cc: In function ‘int main()’:
main.cc:13:12: error: use of deleted function ‘NoDtor::~NoDtor()’
   13 |     NoDtor o1;
      |            ^~
main.cc:6:5: note: declared here
    6 |     ~NoDtor() = delete;
      |     ^
```

报错也只是因为试图销毁局部对象，new出来的对象没人delete，就不会调用到析构函数，也不会报错。

## 与default的区别

=delete必须出现在函数第一次声明的时候，g++貌似有bug?(和g++版本有关)

```cpp
// test4
#include <iostream>

struct NoDtor {
    NoDtor();
    ~NoDtor();

    NoDtor(const NoDtor&);
    NoDtor& operator=(const NoDtor&);
};

NoDtor::NoDtor() = default;
NoDtor::~NoDtor() = delete;
NoDtor::NoDtor(const NoDtor&) = delete;
NoDtor& NoDtor::operator=(const NoDtor&) = delete;

int main() {
    auto p = new NoDtor;

    return 0;
}
```

将=delete放在成员函数定义的时候，用g++编译发现并不报错，但是clang++会明确报错：

```cpp
$ clang++ main.cc  -std=c++11
main.cc:12:21: error: deleted definition must be first declaration
NoDtor::~NoDtor() = delete;
                    ^
main.cc:5:5: note: previous declaration is here
    ~NoDtor();
    ^
main.cc:13:33: error: deleted definition must be first declaration
NoDtor::NoDtor(const NoDtor&) = delete;
                                ^
main.cc:7:5: note: previous declaration is here
    NoDtor(const NoDtor&);
    ^
main.cc:14:44: error: deleted definition must be first declaration
NoDtor& NoDtor::operator=(const NoDtor&) = delete;
                                           ^
main.cc:8:13: note: previous declaration is here
    NoDtor& operator=(const NoDtor&);
            ^
3 errors generated.
```


任意函数都可以声明为=delete, 但只有编译器可以合成的函数可以定义为=default。