#include <iostream>

#include "value_categories.h"

template <typename T>
void foo(T&& arg) {
    boolalpha(std::cout);
    if constexpr (std::is_lvalue_reference_v<T>){
        std::cout << "LVALUE ARGUMENT has been passed to foo()\n";
    } else {
        std::cout << "RVALUE ARGUMENT has been passed to foo()\n";
    }

    std::cout << "std::is_same_v<decltype(arg), T> => " << std::is_same_v<decltype(arg), T> << "\n";
}

template <typename T>
void fum(T arg1, T&& arg2) {
    boolalpha(std::cout);
    std::cout << "fum(T, T&&)\n";
    std::cout << "std::is_same_v<decltype(arg2), T> => " << std::is_same_v<decltype(arg2), T> << "\n";
}

template <typename T>
void zoot(T& arg1, T&& arg2) {
    boolalpha(std::cout);
    std::cout << "zoot(T&, T&&)\n";
    std::cout << "std::is_same_v<decltype(arg2), T> => " << std::is_same_v<decltype(arg2), T> << "\n";
}

template <typename T>
void quux(T arg1, T& arg2) {
    std::cout << "quux(T, T&)\n";
}


/**
 * https://riptutorial.com/cplusplus/example/25566/template-type-deduction
 * @tparam T
 * @param arg1
 * @param arg2
 */
int main(){
    {
        std::cout << "***************1******************\n";
        int y = 10;
        printvalcat<decltype((y))>();
        foo(y);

        printvalcat<decltype((10))>();
        foo(10);

        printvalcat<decltype((std::move(y)))>();
        foo(std::move(y));
        std::cout << "***************1******************\n";
    }
    {
        std::cout << "***************2******************\n";
        int x{}, y{};
        //fum(x, y); //=> conflicting types for parameter T (int vs int&)
        quux(x,y);
        //zoot(x, y); //=> conflicting types for parameter T (int vs int&)
        std::cout << "***************2******************\n";
    }
    {
        std::cout << "***************3******************\n";
        int x{}, y{};
        fum(&x, &x);
        //quux(&x, &y); //=> expects an lvalue for the 2nd arg
        //zoot(&x, &y); //=> expects an lvalue for the 1st arg
        std::cout << "***************3******************\n";
    }
    {
        std::cout << "***************4******************\n";
        int x{}, y{};
        fum(std::move(x), std::move(y));
        //quux(std::move(x), std::move(y)); //=> expects an lvalue for the 2nd arg
        //zoot(std::move(x), std::move(y)); //=> expects an lvalue for the 1st arg
        std::cout << "***************4******************\n";
    }


    return EXIT_SUCCESS;
}

