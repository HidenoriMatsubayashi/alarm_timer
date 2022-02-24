#include <iostream>
#include <memory>

#include "multi_timer.h"
#include "simple_timer.h"

int main() {
  // Simple timer example.
  {
    auto timer = std::make_unique<SimpleTimer>();
    std::chrono::milliseconds duration(50);
    timer->Set(
        []() { std::cout << "Simple Timer fired after 50 msec." << std::endl; },
        duration);
  }

  // Multi timer example.
  auto timer = std::make_unique<MultiTimer>();
  volatile int alarm_count = 0;
  {
    std::chrono::milliseconds duration(1000);
    timer->Set(
        [&]() {
          std::cout << "Multi timer fired after 1000 msec." << std::endl;
          alarm_count++;
        },
        duration);
  }

  {
    std::chrono::milliseconds duration(300);
    timer->Set(
        [&]() {
          std::cout << "Multi timer fired after 300 msec." << std::endl;
          alarm_count++;
        },
        duration);
  }

  while (alarm_count != 2) {
    std::chrono::milliseconds msec(100);
    std::this_thread::sleep_for(msec);
  }

  return 0;
}
