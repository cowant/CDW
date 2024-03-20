# 所有的虚函数都必须有定义

当我们用基类的引用或者指针调用一个虚成员函数时会执行动态绑定，这意味着编译器无法在编译期确定到底会使用哪个虚函数。因此我们直到运行时才能知道到底使用了哪个版本的虚函数，所以所有的虚函数都必须有定义。

```cpp
// test1
#include <iostream>

class B {
public:
    B() = default;
    explicit B(int b) : b_{b} {}
    virtual ~B() = default;

    virtual void Display();

private:
	int b_{0};
};

class D1 : public B {
public:
    D1() = default;
    explicit D1(int d1) : B(), d1_{d1} {}
    ~D1() = default;

    virtual void Display() override {
		std::cout << "D1: " << d1_ << std::endl;
    }
private:
	int d1_{0};
};

int main() {
	D1 d1(10);

	return 0;
}
```

这个例子中基类没有定义虚函数，那么在链接阶段将会报错：

```bash
/usr/bin/ld: /tmp/ccu9GgYS.o: warning: relocation against `_ZTV1B' in read-only section `.text._ZN1BD2Ev[_ZN1BD5Ev]'
/usr/bin/ld: /tmp/ccu9GgYS.o: in function `B::B()':
main.cc:(.text._ZN1BC2Ev[_ZN1BC5Ev]+0xf): undefined reference to `vtable for B'
/usr/bin/ld: /tmp/ccu9GgYS.o: in function `B::~B()':
main.cc:(.text._ZN1BD2Ev[_ZN1BD5Ev]+0xf): undefined reference to `vtable for B'
/usr/bin/ld: /tmp/ccu9GgYS.o:(.data.rel.ro._ZTI2D1[_ZTI2D1]+0x10): undefined reference to `typeinfo for B'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

同样派生类没有定义虚函数，也会报同样的错误：
```cpp
// test2
#include <iostream>

class B {
public:
    B() = default;
    explicit B(int b) : b_{b} {}
    virtual ~B() = default;

    virtual void Display() {
        std::cout << "B: " << b_ << std::endl;
    }

private:
	int b_{0};
};

class D1 : public B {
public:
    D1() = default;
    explicit D1(int d1) : B(), d1_{d1} {}
    ~D1() = default;

    virtual void Display() override;
private:
	int d1_{0};
};

int main() {
	D1 d1(10);

	return 0;
}
```

链接报错：

```bash
/usr/bin/ld: /tmp/ccEGWayq.o: warning: relocation against `_ZTV2D1' in read-only section `.text._ZN2D1D2Ev[_ZN2D1D5Ev]'
/usr/bin/ld: /tmp/ccEGWayq.o: in function `D1::D1(int)':
main.cc:(.text._ZN2D1C2Ei[_ZN2D1C5Ei]+0x22): undefined reference to `vtable for D1'
/usr/bin/ld: /tmp/ccEGWayq.o: in function `D1::~D1()':
main.cc:(.text._ZN2D1D2Ev[_ZN2D1D5Ev]+0x13): undefined reference to `vtable for D1'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

除非我们不定义这样的对象:

```cpp
#include <iostream>

class B {
public:
    B() = default;
    explicit B(int b) : b_{b} {}
    virtual ~B() = default;

    // 虚函数没有定义
    virtual void Display();
private:
	int b_{0};
};

class D1 : public B {
public:
    D1() = default;
    explicit D1(int d1) : B(), d1_{d1} {}
    ~D1() = default;

    // 虚函数没有定义
    virtual void Display() override;
private:
	int d1_{0};
};

int main() {

	return 0;
}
```

