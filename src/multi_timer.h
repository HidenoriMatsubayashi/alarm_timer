#ifndef MULTI_TIMER_H_
#define MULTI_TIMER_H_

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class MultiTimer {
public:
  using callback = std::function<void(void)>;
  using task = std::pair<std::chrono::system_clock::time_point, callback>;

  MultiTimer();
  ~MultiTimer();

  void Set(callback cb, std::chrono::system_clock::duration duration);
  size_t Size();
  bool Empty();

private:
  void Process();

  struct compare {
    bool operator()(const task& a, const task& b) const {
      return a.first > b.first;
    }
  };

  bool is_enabled_;
  std::thread thread_;
  std::condition_variable_any cond_;
  std::recursive_mutex mutex_;
  std::priority_queue<task, std::vector<task>, compare> timer_queue_;
};

#endif // MULTI_TIMER_H_
