#ifndef SORTER_C
#define SORTER_C

#include "Sorter.h"

unsigned int
Sorter::maximum_observers ()
{
  return 100;
}

Sorter::Sorter()
  :observers_(maximum_observers()), 
   num_observers_(0)
{
}

Sorter::~Sorter()
{
}

/*
register_observer registers the observer into an array by calling set_observer.
*/
int Sorter::register_observer(Sort_Observer &sort_observer)
{
  if (num_observers_ < maximum_observers() ) {
    set_observer(num_observers_, &sort_observer);
    num_observers_++;
    return 0;
  }
  return -1;
}

/*
publish_sort_update sends an update to every observer in the array.
*/
void Sorter::publish_sort_update(const Sort_Info_Base &sort_observation)
{
  for (int i = 0; i < num_observers_; i++) {
    observers_[i]->update_sort(sort_observation);
  }
}

/* ---- Auxiliary Functions -------- */

/*
set_observer adds an observer to the array of observers
*/
int Sorter::set_observer(unsigned int i, Sort_Observer *sort_observer)
{
  return observers_.set(i, sort_observer);
}

/*
get_observer gets the observer at index i of the array.
*/
Sort_Observer* Sorter::get_observer(unsigned int i)
{
  Sort_Observer* temp;
  observers_.get(i, temp);
  return temp;
}

#endif
