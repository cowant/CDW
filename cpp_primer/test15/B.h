using TD = double;

class A {
public:
    A() = default;

    TD F2() {
        return a_;
    }
public:
    using TD = double;

private:
    TD a_{0};
};
