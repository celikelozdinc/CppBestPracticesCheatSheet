#ifndef CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_CSDEVICE_H
#define CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_CSDEVICE_H

#include "device.h"
#include <memory>

namespace Drivers {
  struct Impl {
    uint8_t counter{UINT8_MAX -1};
    std::unique_ptr<char[]> indicator {std::make_unique<char[]>(3)};
  };
}

#endif // CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_CSDEVICE_H
