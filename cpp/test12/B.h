#ifndef _B_H_
#define _B_H_

#include <iostream>
#include <string>
#include <format>

class A;

class B {
friend std::ostream& operator<<(std::ostream &out, const B& b);
public:
    B();
    B(int a, const std::string &s);

    B& CopyFrom(const A& a);
private:
    int a_{20};
    std::string s_{"B"};
};

#endif
