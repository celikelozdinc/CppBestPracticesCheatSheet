#include "EFDevice.h"

#include <iostream>

//g++ -c link_time_polymorphism/EFDevice.cpp -o link_time_polymorphism/obj/EFDevice.o
namespace Drivers {
  DeviceDriver::DeviceDriver(std::unique_ptr<Impl> p) {
    this->pIml = std::move(p);
    std::cout << "DeviceDriver::DeviceDriver(std::unique_ptr<Impl>)\n";
    std::cout << "Counter -> " << this->pIml->counter << "\n";
    std::cout << "Indicator -> " << this->pIml->indicator << "\n";
  }
  DeviceDriver::~DeviceDriver() {
    std::cout << "DeviceDriver::~DeviceDriver()\n";
    this->pIml.reset(nullptr);
  }
}
