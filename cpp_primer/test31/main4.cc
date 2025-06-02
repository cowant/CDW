#include <iostream>

class B {
public:
    B() = default;
    B(int i) : a_{i} {}
    virtual ~B() = default;
    void Addr() const {
        std::cout << "object @ " << this << std::endl;
    }
private:
    int a_{10};
};

class D1 : public B {
public:
    D1() = default;
    D1(int i) : B(i), b_{i} {}
    ~D1() = default;

private:
    int b_{100};
};

class D2 : protected B {
public:
    D2() = default;
    D2(int i) : B(i), b_{i} {}
    ~D2() = default;

private:
    int b_{100};
};

class D3 : private B {
public:
    D3() = default;
    D3(int i) : B(i), b_{i} {}
    ~D3() = default;

private:
    int b_{100};
};

class DD1 : public D1 {
public:
    DD1() = default;
    DD1(int i) : D1(i), c_{i} {}
    ~DD1() = default;

    void Foo() const {
        // D1使用public继承B，那么D1转换为B显然是没啥问题的
        B *b = new D1(100);
        b->Addr();
    }

private:
    int c_{100};
};

class DD2 : public D2 {
public:
    DD2() = default;
    DD2(int i) : D2(i), c_{i} {}
    ~DD2() = default;

    void Foo() const {
        // D2使用protected继承B，为啥在这里也能转换为B ？？？显然，如果是在
        // 用户代码中这么转换，肯定是不能通过编译的，但这里是在DD2的成员函数
        // 中，编译器支持这么转换，或许可以这么理解：
        //
        // DD2的成员函数可以访问D2的public和protected成员，而D2采用protected
        // 说明符继承B，那么可以认为B的成员位于D2的protected部分，所以DD2是可以
        // 访问B的public和protected成员的，于是D2可以向B转换。
        //
        B *b = new D2(100);
        b->Addr();
    }

private:
    int c_{100};
};

class DD3 : public D3 {
public:
    DD3() = default;
    DD3(int i) : D3(i), c_{i} {}
    ~DD3() = default;

    void Foo() const {
        // D3使用private继承B，那么D3转换为B显然是不允许的
        B *b = new D3(100);
        b->Addr();
    }

private:
    int c_{100};
};

int main() {
    auto p1 = new DD1(10000);
    auto p2 = new DD2(20000);
    auto p3 = new DD3(30000);

    p1->Foo();
    p2->Foo();
    p3->Foo();

    return 0;
}
