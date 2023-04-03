#include "fubar.h"

#include <iostream>

void fubar(int j) {
  std::cout << "fubar.cpp::fubar() => Current static global variable : " << Zot::myStaticString << "\n";
  std::cout << "bar.cpp::bar() => Current constexpr global variable : " << myMacro << "\n";
  std::cout << "fubar.cpp::fubar() => Current common variable : " << commonVar << "\n";
  commonVar = 41;
  std::cout << "fubar.cpp::fubar() => Updated common variable : " << commonVar << "\n";
}