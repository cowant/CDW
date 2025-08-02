template <typename T = int>
class Numbers {
public:
    Numbers(T v = 0) : val{v} {}
private:
    T val;
};

int main() {
    Numbers<double> v1;
    Numbers<> v2;

    return 0;
}
