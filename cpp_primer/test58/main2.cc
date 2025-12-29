int main() {
    int i = 0;
    int& r2 = i;

    int&& r3 = static_cast<int&&>(i);
    int&& r4 = static_cast<int&&>(r2);

    return 0;
}
