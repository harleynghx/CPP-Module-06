#include <iostream>

int main() {
    double zero = 0.0;
    double myInf = 1.0 / zero;
    double myNan = zero / zero;

    std::cout << "INF: " << myInf << std::endl;
    std::cout << "NAN: " << myNan << std::endl;
}