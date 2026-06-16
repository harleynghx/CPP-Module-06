#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cerrno>

// Private OCF to prevent instantiation (subject PDF)
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &src) { (void)src; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &src) { (void)src; return *this; }
ScalarConverter::~ScalarConverter() {}

// check for NaN (Not a Number)
static bool isNaN(double value) {
    return value != value;
}

// check for positive or negative infinity 
static bool isInf(double value) {
    return value == std::numeric_limits<double>::infinity() ||
           value == -std::numeric_limits<double>::infinity();
}

// Converts the parsed double value to char and prints it, or prints "impossible"/"Non displayable"
static void printChar(double value) {
    std::cout << "char: ";
    if (isNaN(value) || isInf(value) || value < 0 || value > 127) {
        std::cout << "impossible\n";
    } else {
        char c = static_cast<char>(value);
        if (std::isprint(static_cast<unsigned char>(c))) {
            std::cout << "'" << c << "'\n";
        } else {
            std::cout << "Non displayable\n";
        }
    }
}

// Converts the parsed double value to int and prints it, checking for overflow bounds
static void printInt(double value) {
    std::cout << "int: ";
    if (isNaN(value) || isInf(value) ||
        value < static_cast<double>(std::numeric_limits<int>::min()) ||
        value > static_cast<double>(std::numeric_limits<int>::max())) {
        std::cout << "impossible\n";
    } else {
        std::cout << static_cast<int>(value) << "\n";
    }
}

// Converts the parsed double value to float and prints it with a precision of 1 decimal place and suffix 'f'
static void printFloat(double value) {
    std::cout << "float: ";
    float f = static_cast<float>(value);
    if (isNaN(f)) {
        std::cout << "nanf\n";
    } else if (isInf(f)) {
        std::cout << (f > 0 ? "+inff" : "-inff") << "\n";
    } else {
        std::cout << std::fixed << std::setprecision(1) << f << "f\n";
    }
}

// Converts the parsed double value to double and prints it with a precision of 1 decimal place
static void printDouble(double value) {
    std::cout << "double: ";
    if (isNaN(value)) {
        std::cout << "nan\n";
    } else if (isInf(value)) {
        std::cout << (value > 0 ? "+inf" : "-inf") << "\n";
    } else {
        std::cout << std::fixed << std::setprecision(1) << value << "\n";
    }
}

// Main static convert method: detects the literal type of the input string,
// parses/converts it to actual numeric values, and handles outputs for char, int, float, and double.
void ScalarConverter::convert(const std::string &s) {
    if (s.empty()) {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: impossible\n"
                  << "double: impossible\n";
        return;
    }

    // Check for "char literal" without quotes, e.g. a
    if (s.length() == 1 && !std::isdigit(s[0])) {
        // cast to <double> to get ascii value
        double value = static_cast<double>(s[0]);
        printChar(value);
        printInt(value);
        printFloat(value);
        printDouble(value);
        return;
    }

    // Check for "char literal" with quotes, e.g. 'a'
    if (s.length() == 3 && s[0] == '\'' && s[2] == '\'') {
        double value = static_cast<double>(s[1]);
        printChar(value);
        printInt(value);
        printFloat(value);
        printDouble(value);
        return;
    }

    // Check for pseudo literals
    if (s == "nan" || s == "nanf") {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: nanf\n"
                  << "double: nan\n";
        return;
    }
    if (s == "+inf" || s == "+inff" || s == "inf" || s == "inff") {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: inff\n"
                  << "double: inf\n";
        return;
    }
    if (s == "-inf" || s == "-inff") {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: -inff\n"
                  << "double: -inf\n";
        return;
    }



    // Try parsing as numeric literal
    char *endptr;
    errno = 0;
    double value = std::strtod(s.c_str(), &endptr);



    // If == true means the pointer nvr moved (strtod failed)
    if (endptr == s.c_str()) {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: impossible\n"
                  << "double: impossible\n";
        return;
    }

    // Check if there are invalid trailing characters.
    if (*endptr != '\0') {
        // check if remaining is just 'f' or 'F'
        if ((*endptr == 'f' || *endptr == 'F') && *(endptr + 1) == '\0') {
            // Valid float literal suffix
        } else {
            std::cout << "char: impossible\n"
                      << "int: impossible\n"
                      << "float: impossible\n"
                      << "double: impossible\n";
            return;
        }
    }

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}