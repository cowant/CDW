template <typename T>
class A {
friend class T;
friend int;
friend double;
public:
  A() = default;
  A(int d) : d_{d} {}
private:
  int d_{10};
};
