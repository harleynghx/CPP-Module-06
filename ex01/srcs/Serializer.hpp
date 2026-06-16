#pragma once
#include <stdint.h>
#include "Data.hpp"

class Serializer {
private:
    // Private constructors and destructors to prevent instantiation (Orthodox Canonical Form)
    Serializer();
    Serializer(const Serializer &src);
    Serializer &operator=(const Serializer &src);
    ~Serializer();

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
