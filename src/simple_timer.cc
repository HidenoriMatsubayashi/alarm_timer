#include "simple_timer.h"

#include <chrono>
#include <iostream>

SimpleTimer::~SimpleTimer() {
  if (thread_.joinable()) {
    thread_.join();
  }
}

void SimpleTimer::Set(std::function<void(void)> callback, int interval_sec) {
  thread_ = std::thread([callback, interval_sec]() {
    std::chrono::seconds sec(interval_sec);
    std::this_thread::sleep_for(sec);
    callback();
  });
}
