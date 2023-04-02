#include "common.h"

int _extern{17};

void foo(int i) {
  std::cout << "common.cpp::foo(i) starts for i => " << i << "\n";
  std::cout << "common.cpp::_extern =>" << _extern << "\n";
}


