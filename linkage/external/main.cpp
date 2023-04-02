#include <iostream>

extern void bar(int j);
extern void fubar(int i);
extern void baz(int i);

/**
 *  g++ linkage/external/main.cpp linkage/external/bar.cpp linkage/external/fubar.cpp linkage/external/common.cpp -o linkage/external/main
 * @return
 */
int main() {
  std::cout << "++++++++++\n";
  bar(11);
  std::cout << "----------\n";

  std::cout << "++++++++++\n";
  baz(22);
  std::cout << "----------\n";

  std::cout << "++++++++++\n";
  fubar(33);
  std::cout << "----------\n";
  return EXIT_SUCCESS;
}
