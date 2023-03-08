#include "CSDevice.h"

#include <iostream>

//g++ -c link_time_polymorphism/CSDevice.cpp -o link_time_polymorphism/obj/CSDevice.o
namespace Drivers {
  DeviceDriver::DeviceDriver(std::unique_ptr<Impl> p) {
    this->pIml = std::move(p);
    this->pIml->indicator[0] = 'C';
    this->pIml->indicator[1] = 'S';
    this->pIml->indicator[2] = 'D';
    std::cout << "DeviceDriver::DeviceDriver(std::unique_ptr<Impl>)\n";
    std::cout << "Counter -> " << this->pIml->counter << "\n";
    std::cout << "Indicator -> " << this->pIml->indicator[0] << "." << this->pIml->indicator[1] << "." << this->pIml->indicator[2] << "\n";
  }

  DeviceDriver::~DeviceDriver() {
    std::cout << "DeviceDriver::~DeviceDriver()\n";
    this->pIml.reset(nullptr);
  }

}
