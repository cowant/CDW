#include <iostream>

class Student {
public:
    // 定义一个静态成员函数，返回指向私有成员的指针
    static int Student::* getScorePointer() {
        return &Student::score; // 类内部可以访问私有成员
    }
private:
    int score = 100;
};

int main() {
    // 即使 score 是私有的，我们也可以通过合法的入口获取它的“位置”
    int Student::* p = Student::getScorePointer();

    Student s;
    // 使用时依然需要遵循成员指针的语法
    std::cout << "Private score via pointer: " << s.*p << std::endl;

    return 0;
}
