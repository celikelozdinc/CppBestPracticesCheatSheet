#include "bar.h"

#include <iostream>

void bar(int j) {
  std::cout << "bar.cpp::bar() => Current static global variable : " << Zot::myStaticString << "\n";
  std::cout << "bar.cpp::bar() => Current constexpr global variable : " << myMacro << "\n";
  std::cout << "bar.cpp::bar() => Current common variable : " << commonVar << "\n";
  commonVar = 17;
  std::cout << "bar.cpp::bar() => Updated common variable : " << commonVar << "\n";
}
