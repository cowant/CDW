using TD = double;

class A {
public:
    using TD = int;

    A() = default;

    TD F2() {
        return a_;
    }

private:
    TD a_{0};
};
