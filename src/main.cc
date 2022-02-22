#include <iostream>
#include <memory>

#include "simple_timer.h"

int main() {
  auto simple_timer = std::make_unique<SimpleTimer>();
  simple_timer->Set([]() { std::cout << "Simple Timer Alarm" << std::endl; },
                    1);
  return 0;
}
