#include <iostream>
#include <string>

class Student {
public:
    std::string name;
    int score;
};

int main() {
    // 1. 定义一个指向 Student 类中 int 成员的指针
    int Student::* pScore = &Student::score;

    Student s1;
    s1.score = 95;

    // 2. 通过成员指针访问 s1 的数据
    std::cout << "Score of s1: " << s1.*pScore << std::endl; // 输出 95

    Student* sPtr = new Student { "Alice", 100 };
    // 3. 通过对象指针和成员指针访问数据
    std::cout << "Score of Alice: " << sPtr->*pScore << std::endl; // 输出 100

    delete sPtr;
    return 0;
}
