#include "multi_timer.h"

#include <iostream>

MultiTimer::MultiTimer() {
  is_enabled_ = true;
  thread_ = std::thread(&MultiTimer::Process, this);
}

MultiTimer::~MultiTimer() {
  is_enabled_ = false;
  cond_.notify_one();
  if (thread_.joinable()) {
    thread_.join();
  }
}

void MultiTimer::Set(callback cb,
                     std::chrono::system_clock::duration duration) {
  std::lock_guard<std::recursive_mutex> lk(mutex_);
  auto tp = std::chrono::system_clock::now() + duration;
  timer_queue_.push({tp, cb});
  cond_.notify_one();
}

bool MultiTimer::Empty() {
  std::lock_guard<std::recursive_mutex> lk(mutex_);
  return timer_queue_.empty();
}

size_t MultiTimer::Size() {
  std::lock_guard<std::recursive_mutex> lk(mutex_);
  return timer_queue_.size();
}

void MultiTimer::Process() {
  std::unique_lock<std::recursive_mutex> lk(mutex_);
  while (is_enabled_) {
    if (timer_queue_.empty()) {
      // Sleep until an alarm set.
      cond_.wait(lk, [&]() { return !is_enabled_ || !timer_queue_.empty(); });
    } else {
      auto next_tp = timer_queue_.top().first;

      // Sleep until the next time point.
      cond_.wait_until(lk, next_tp, [&]() {
        auto now = std::chrono::system_clock::now();
        return !is_enabled_ || (!timer_queue_.empty() && next_tp <= now);
      });

      while (is_enabled_ && !timer_queue_.empty() &&
             timer_queue_.top().first <= std::chrono::system_clock::now()) {
        auto alarm_cb = std::move(timer_queue_.top().second);
        timer_queue_.pop();
        alarm_cb();
      }
    }
  }
}
