#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &);
    ScalarConverter &operator=(const ScalarConverter &);
    ~ScalarConverter();
public:
    static void convert(const std::string &s);
};
