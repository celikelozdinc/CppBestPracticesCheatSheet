#include <iostream>

#include "common.h"
#include "bar.h"
#include "fubar.h"

/**
 *  g++ -std=c++14 linkage/internal/bar.cpp linkage/internal/fubar.cpp linkage/internal/main.cpp -o linkage/internal/main
 *  g++ -std=c++17 linkage/internal/bar.cpp linkage/internal/fubar.cpp linkage/internal/main.cpp -o linkage/internal/main
 *  http://www.goldsborough.me/c/c++/linker/2016/03/30/19-34-25-internal_and_external_linkage_in_c++/
 *  https://pabloariasal.github.io/2019/02/28/cpp-inlining/
 */
int main() {
  std::cout << "++++++++++\n";
  std::cout << "main.cpp => Current static global variable : " << Zot::myStaticString << "\n";
  std::cout << "main.cpp => Current constexpr global variable : " << myMacro << "\n";
  printer();
  std::cout << "----------\n";

  std::cout << "++++++++++\n";
  bar(11);
  std::cout << "----------\n";

  std::cout << "++++++++++\n";
  baz();
  std::cout << "----------\n";

  std::cout << "++++++++++\n";
  fubar(33);
  std::cout << "----------\n";

  return EXIT_SUCCESS;
}
