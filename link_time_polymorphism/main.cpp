#include "EFDevice.h"
#include "CSDevice.h"

#include <iostream>

//g++ -c link_time_polymorphism/EFDevice.cpp -o link_time_polymorphism/obj/EFDevice.o
//g++ -c link_time_polymorphism/CSDevice.cpp -o link_time_polymorphism/obj/CSDevice.o
//g++ -c link_time_polymorphism/main.cpp -o link_time_polymorphism/obj/main.o

//g++ link_time_polymorphism/obj/main.o link_time_polymorphism/obj/EFDevice.o -o link_time_polymorphism/obj/exec
//g++ link_time_polymorphism/obj/main.o link_time_polymorphism/obj/CSDevice.o -o link_time_polymorphism/obj/exec

//./link_time_polymorphism/obj/exec
int main() {

  std::unique_ptr<Drivers::Impl> pImpl  = std::make_unique<Drivers::Impl>();
  Drivers::DeviceDriver driver{std::move(pImpl)};

  return EXIT_SUCCESS;
}