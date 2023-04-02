#ifndef CPPBESTPRACTICESCHEATSHEET_LINKAGE_EXTERNAL_COMMON_H
#define CPPBESTPRACTICESCHEATSHEET_LINKAGE_EXTERNAL_COMMON_H

#include <iostream>

extern void foo(int i); //declaration
extern int _extern; //declaration
//int _extern{77}; //definition

//definition
extern void baz(int i) {
  std::cout << "common.h::baz() => " << i << "\n";
}


#endif
