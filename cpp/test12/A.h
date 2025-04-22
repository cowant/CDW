#ifndef _A_H_
#define _A_H_

#include <iostream>
#include <string>
#include <format>

class A {
friend class B;
friend std::ostream& operator<<(std::ostream &out, const A& a);
public:
    A();
    A(int a, const std::string &s);
private:
    int a_{10};
    std::string s_{"A"};
};

#endif
