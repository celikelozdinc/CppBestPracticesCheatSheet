#ifndef CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_CSDEVICE_H
#define CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_CSDEVICE_H

//g++ -c link_time_polymorphism/CSDevice.cpp -o link_time_polymorphism/obj/CSDevice.o
#include "device.h"
#include <memory>

namespace Drivers {
  struct Impl {
    uint8_t counter{UINT8_MAX -1};
    std::unique_ptr<char[]> indicator {std::make_unique<char[]>(3)};
  };
}

#endif // CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_CSDEVICE_H
