#include <iostream>

class B {
public:
    B() = default;
    explicit B(int b) : b_{b} {}
    virtual ~B() = default;

    void Display() {
		std::cout << "B" << std::endl;
	}
private:
	int b_{0};
};

class D1 : public B {
public:
    D1() = default;
    explicit D1(int d1) : B(), d1_{d1} {}
    ~D1() = default;

    virtual void Display() {
		std::cout << "D1" << std::endl;
	}
private:
	int d1_{0};
};

int main() {
	B *pb0 = new B(10);
	B *pb1 = new D1(100);

	pb0->Display();
	pb1->Display();

	return 0;
}
