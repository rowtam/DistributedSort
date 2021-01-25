#include <sys/time.h>
#include <iostream.h>

class Timer {
 public:
  Timer();
  ~Timer();
  void start_time();
  void stop_time();
  void display_time();

  enum status{
	started,
	stopped,
	never_started
  };

  status status_;

 private:
  hrtime_t start;
  hrtime_t stop;
};
