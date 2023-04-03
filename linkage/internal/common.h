#ifndef CPPBESTPRACTICESCHEATSHEET_LINKAGE_INTERNAL_COMMON_H
#define CPPBESTPRACTICESCHEATSHEET_LINKAGE_INTERNAL_COMMON_H

#include <string_view>
#include <iostream>

static int commonVar{42};

/**
 * const and constexpr global variables have internal linkage by default
 * and thus don’t need the static keyword
 */
constexpr int myMacro{17};

/**
 * C++17 extends the concept of inlining to variables
 */
inline void baz() {
  std::cout << "common.h::baz()\n";
}

inline static void printer() {
  std::cout << "common.h::printer()\n";
}

// Breaks ODR
//void fum() {;}

/**
 * inline variables are only available with ‘-std=c++17’ or ‘-std=gnu++17’
 */
struct Zot {
  //static std::string myStaticString{"My static string has static storage duration"}; //=>  non-constant in-class initialization invalid for non-inline static member
  inline static std::string myStaticString{"My static string has static storage duration"};
  //inline static std::string_view myStaticString{"My static string has static storage duration"};
};


#endif
