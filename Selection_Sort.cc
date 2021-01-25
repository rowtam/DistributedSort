#ifndef SELECTION_SORT_C
#define SELECTION_SORT_C

#include "Selection_Sort.h"
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>  /* for close () and sleep () */
#include "Timer.h"


/*
The progress_ enum type keeps track of the current state of this
Sorter object.  Although, it's not really necessary.
*/
template <class T>
Selection_Sort<T>::Selection_Sort(const Sort_Info<T> &s)
  :array_data_(s.data())
{
  progress_ = Selection_Sort::NOT_STARTED;
}

/*
Destructor
*/
template <class T>
Selection_Sort<T>::~Selection_Sort()
{
}

/*
start_sort performs selection sort on the array and updates the observers as necessary
*/
template <class T>
int Selection_Sort<T>::start_sort()
{
  if (progress_ != Selection_Sort::NOT_STARTED) {
    cout << "Sort is either in progress or finished." << endl;
    return -1;
  }
  cout << "Selection Sort Start" << endl;
  progress_ = Selection_Sort::STARTED;
  Timer t;
  t.start_time();
  int i;
  int j;
  int smallest;
  for (i = 0; i < array_data_.size()-1; i++) {
    smallest = i;
    for (j = i+1; j < array_data_.size(); j++) {
      if (array_data_[j] < array_data_[smallest])
        smallest = j;
    }
    T temp1;
    temp1 = array_data_[smallest];
    array_data_[smallest] = array_data_[i];
    array_data_[i] = temp1;    
  }
  t.stop_time();
  cout << "Selection Sort Stop" << endl;
  cout << "Selection Sort Time" << endl;
  t.display_time();
  Sort_Info<T> answer(Sort_Info_Base::SELECTION_SORT, array_data_,
	Sort_Info_Base::SORTED);
  publish_sort_update(answer);
  progress_ = Selection_Sort::FINISHED;
  return 0;
}

#endif
