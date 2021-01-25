#ifndef QUICK_SORT_C
#define QUICK_SORT_C

#include "Quick_Sort.h"
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
Quick_Sort<T>::Quick_Sort(const Sort_Info<T> &s)
  :array_data_(s.data())
{
  progress_ = Quick_Sort::NOT_STARTED;
}

/*
Destructor

*/
template <class T>
Quick_Sort<T>::~Quick_Sort()
{
}

/*
start_sort performs selection sort on the array and updates the observers as necessary
*/
template <class T>
int Quick_Sort<T>::start_sort()
{
  if (progress_ != Quick_Sort::NOT_STARTED) {
    cout << "Sort is either in progress or finished." << endl;
    return -1;
  }
  progress_ = Quick_Sort::STARTED;
  Timer t;
  cout << "Quick Sort Start" << endl;
  cout << "Array of Size: " << array_data_.size() << endl;
  t.start_time();
  QSort(array_data_, 0, array_data_.size() - 1);
  t.stop_time();
  cout << "Quick Sort Stop" << endl;
  cout << "Quick Sort Time" << endl;
  t.display_time();
  Sort_Info<T> answer(Sort_Info_Base::QUICK_SORT, array_data_,
	Sort_Info_Base::SORTED);
  publish_sort_update(answer);
  progress_ = Quick_Sort::FINISHED;
  return 0;
}

/*
Quick Sort
 */
template <class T>
void Quick_Sort<T>::QSort(Array<T>& a, int first, int last)
{
  int pivindx;
  if (last > first) {
    pivindx = Partition(a, first, last);
    QSort(a, first, pivindx - 1);
    QSort(a, pivindx + 1, last);
  }
}

/*
Partition
 */
template <class T>
int Quick_Sort<T>::Partition(Array<T>& a, int first, int last)
{
  int pivindx, top, i;
  T pivot;
  i = rand() % (last - first + 1) + first;
  pivot = a[i];
  a[i] = a[first];
  a[first] = pivot;
  pivindx = first;
  top = last;
  while (top > pivindx) {
    if (a[top] >= pivot) {
      --top;
    } else {
      a[pivindx] = a[top];
      a[top] = a[pivindx + 1];
      a[pivindx + 1] = pivot;
      ++pivindx;
    }
  }
  return pivindx;
}

#endif
