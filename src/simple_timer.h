#ifndef SIMPLE_TIMER_H_
#define SIMPLE_TIMER_H_

#include <functional>
#include <thread>

class SimpleTimer {
public:
  using callback = std::function<void(void)>;

  SimpleTimer() = default;
  ~SimpleTimer();

  void Set(callback cb, std::chrono::system_clock::duration duration);

private:
  std::thread thread_;
};

#endif // SIMPLE_TIMER_H_
