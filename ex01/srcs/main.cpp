#include <iostream>
#include "Serializer.hpp"

int main() {
    std::cout << "--- Initializing Data ---\n";
    Data myData;
    myData.s_val = "Hello 42!";
    myData.i_val = 42;
    myData.f_val = 42.42f;

    std::cout << "Original Data Address: " << &myData << "\n";
    std::cout << "s_val: " << myData.s_val << "\n";
    std::cout << "i_val: " << myData.i_val << "\n";
    std::cout << "f_val: " << myData.f_val << "\n\n";

    std::cout << "--- Serializing ---\n";
    uintptr_t raw = Serializer::serialize(&myData);
    std::cout << "Serialized raw uintptr_t value: " << raw << " (Hex: 0x" << std::hex << raw << std::dec << ")\n\n";

    std::cout << "--- Deserializing ---\n";
    Data* deserializedPtr = Serializer::deserialize(raw);
    std::cout << "Deserialized Data Address: " << deserializedPtr << "\n\n";

    std::cout << "--- Verification ---\n";
    if (deserializedPtr == &myData) {
        std::cout << "SUCCESS: The deserialized pointer is EQUAL to the original pointer!\n";
    } else {
        std::cout << "FAILURE: The deserialized pointer is NOT equal to the original pointer!\n";
    }

    std::cout << "s_val from deserialized pointer: " << deserializedPtr->s_val << "\n";
    std::cout << "i_val from deserialized pointer: " << deserializedPtr->i_val << "\n";
    std::cout << "f_val from deserialized pointer: " << deserializedPtr->f_val << "\n";

    return 0;
}
