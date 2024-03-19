#pragma once

struct NoDtor {
    NoDtor();
    ~NoDtor();

    NoDtor(const NoDtor&);
    NoDtor& operator=(const NoDtor&);
};
