#include "EFDevice.h"

int main() {

  std::unique_ptr<Drivers::Impl> pImpl  = std::make_unique<Drivers::Impl>();
  Drivers::DeviceDriver driver{std::move(pImpl)};

  return EXIT_SUCCESS;
}