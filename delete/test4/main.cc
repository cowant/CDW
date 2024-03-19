struct NoDtor {
    NoDtor();
    ~NoDtor();

    NoDtor(const NoDtor&);
    NoDtor& operator=(const NoDtor&);
};

NoDtor::NoDtor() = default;
NoDtor::~NoDtor() = delete;
NoDtor::NoDtor(const NoDtor&) = delete;
NoDtor& NoDtor::operator=(const NoDtor&) = delete;

int main() {
    auto p = new NoDtor;

    return 0;
}
