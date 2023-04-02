#include "bar.h"

extern int _extern;
extern void foo(int i);
extern void baz(int i);

void bar(int j) {
  baz(j);
  std::cout << "bar.cpp::_extern => " << _extern << "\n";
  foo(j);
}
