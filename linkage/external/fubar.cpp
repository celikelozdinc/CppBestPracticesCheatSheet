#include "fubar.h"

//fwd declarations
extern int _extern;
extern void foo(int i);

void fubar(int j) {
  std::cout << "fubar.cpp::_extern =>" << _extern << "\n";
  foo(j);
}