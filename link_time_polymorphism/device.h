#ifndef CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_DEVICE_H
#define CPPBESTPRACTICESCHEATSHEET_LINK_TIME_POLYMORPHISM_DEVICE_H

#include <memory>

namespace Drivers {

  class Impl; // Fwd declaration

  class DeviceDriver{
  public:
    DeviceDriver(std::unique_ptr<Impl>);
    ~DeviceDriver();
  private:
    std::unique_ptr<Impl> pIml;
  };


}

#endif // CPPBESTPRACTICESCHEATSHEET_DEVICE_H
