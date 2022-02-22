#ifndef SIMPLE_TIMER_H_
#define SIMPLE_TIMER_H_

#include <functional>
#include <thread>

class SimpleTimer {
 public:
  SimpleTimer() = default;
  ~SimpleTimer();

  void Set(std::function<void(void)> callback, int interval_sec);

 private:
  std::thread thread_;
};

#endif  // SIMPLE_TIMER_H_
