#ifndef _B_H_
#define _B_H_

#include <iostream>
#include <sstream>
#include <format>

class A;

class B {
public:
    B(std::ostringstream &out);
    void Display() const;
    void Serialize(const A&);
private:
    std::ostringstream &out_;
};

#endif
