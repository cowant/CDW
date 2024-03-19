#include "NoDtor.h"


NoDtor::NoDtor() = default;
NoDtor::~NoDtor() = delete;
NoDtor::NoDtor(const NoDtor&) = delete;
NoDtor& NoDtor::operator=(const NoDtor&) = delete;
