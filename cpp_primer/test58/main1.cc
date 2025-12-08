template <typename T>
void Func(T&& a) {
    T i = 5;
}

int main() {
    int i = 0;
    Func(i); // 错误, T = int&
    Func(5); // 正确, T = int

    return 0;
}
