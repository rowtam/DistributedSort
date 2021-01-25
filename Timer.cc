#include "Timer.h"

Timer::Timer()
{
  status_ = Timer::never_started;
}

Timer::~Timer()
{
}

void Timer::start_time()
{
  if (status_ == Timer::started) {
	cout << "Timer already started." << endl;
  } else {
	status_ = Timer::started;
	start = ::gethrtime();
  }
}

void Timer::stop_time()
{
  if (status_ == Timer::never_started) {
	cout << "Can't call stop_time unless timer was started." << endl;
  } else {
    status_ = Timer::stopped;
    stop = ::gethrtime();
  }
}

void Timer::display_time()
{
  cout << "Total time for operation: " << stop - start << endl;
}
