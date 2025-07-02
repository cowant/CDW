template <typename T>
class A {
friend T;
public:
  A() = default;
  A(int d) : d_{d} {}
private:
  int d_{10};
};
