#include "simple_timer.h"

#include <chrono>
#include <iostream>

SimpleTimer::~SimpleTimer() {
  if (thread_.joinable()) {
    thread_.join();
  }
}

void SimpleTimer::Set(callback cb,
                      std::chrono::system_clock::duration duration) {
  thread_ = std::thread([cb, duration]() {
    std::this_thread::sleep_for(duration);
    cb();
  });
}
