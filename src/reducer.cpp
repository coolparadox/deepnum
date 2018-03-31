#include <iostream>
#include <config.h>

void yo() {
  std::cout
    << "Yo!" << std::endl
    << "This is " PACKAGE_STRING "." << std::endl;
}
