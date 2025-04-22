#ifndef _A_H_
#define _A_H_

#include "B.h"

class A {
friend void B::Serialize(const A&);
public:
    A();
    A(int a, int b);

    void Display() const;
private:
    int a_{10};
    int b_{20};
};

#endif
