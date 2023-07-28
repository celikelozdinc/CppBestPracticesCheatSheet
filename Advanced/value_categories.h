#ifndef CPPBESTPRACTICESCHEATSHEET_VALUE_CATEGORIES_H
#define CPPBESTPRACTICESCHEATSHEET_VALUE_CATEGORIES_H
#include <iostream>

template <typename T>
void printvalcat() {
    if constexpr(std::is_rvalue_reference_v<T>) {
        std::cout << "XVALUE\n";
    } else if constexpr (std::is_lvalue_reference_v<T>) {
        std::cout << "LVALUE\n";
    } else if constexpr (!std::is_reference_v<T>) {
        std::cout << "PRVALUE\n";
    } else {
        std::cout << "UNDEFINED VALUE CATEGORY\n";
    }
}


#endif //CPPBESTPRACTICESCHEATSHEET_VALUE_CATEGORIES_H
