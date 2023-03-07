#ifndef CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_EFDEVICE_H
#define CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_EFDEVICE_H

//g++ -c link_time_polymorphism/EFDevice.cpp -o link_time_polymorphism/obj/EFDevice.o
#include "device.h"
#include <string>

namespace Drivers {
  struct Impl {
    uint64_t counter{100};
    std::string indicator{"ExpensiveFastDevice"};
  };
}

#endif // CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_EFDEVICE_H
