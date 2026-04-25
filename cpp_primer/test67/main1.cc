#include <iostream>
using namespace std;

union Data {
    int i;
    float f;
    char str[4];
};

int main() {
    Data data;
    
    data.i = 10;
    cout << "data.i: " << data.i << endl;

    data.f = 220.5; // 这会覆盖掉之前的整数10
    cout << "data.f: " << data.f << endl;
    
    // 注意：此时再打印 data.i，会得到一个无意义的垃圾值
    cout << "data.i now: " << data.i << endl; 
    
    return 0;
}
