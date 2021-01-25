#ifndef MERGE_SORT_C
#define MERGE_SORT_C

#include "Merge_Sort.h"
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>  /* for close () and sleep () */
#include "Merge_Observer.h"
#include "Timer.h"

/*
The progress_ enum type keeps track of the current state of this
Sorter object.  Although, it's not really necessary.
*/
template <class T>
Merge_Sort<T>::Merge_Sort(const Sort_Info<T> &s)
  :array_data_(s.data())
{
  mode_ = Merge_Sort::MERGE_SORT;
  progress_ = Merge_Sort::NOT_STARTED;
}

/*
This constructor causes Merge_Sort to run in "Super_Merge" mode.
 */
template <class T>
Merge_Sort<T>::Merge_Sort(const Array<Sort_Info<T>*> &s)
  :Sort_Info_Array_(s)
{
  mode_ = Merge_Sort::SUPER_MERGE;
  progress_ = Merge_Sort::NOT_STARTED;
}

/*
This is standard in-place MergeSort.
 */
template <class T>
void Merge_Sort<T>::MergeSort(Array<T>& a, int first, int last)
{
  int mid;
  if (first < last)
  {
    mid = (first + last)/2;
    MergeSort(a, first, mid);
    MergeSort(a, mid + 1, last);
    Merge(a, first, mid, last);
  }
}

/*
Merge is a helper for MergeSort
 */
template <class T>
void Merge_Sort<T>::Merge(Array<T>& a, int first, int mid, int last)
{
  Array<T> temp(a.size());
  int first1 = first;
  int last1 = mid;
  int first2 = mid + 1;
  int last2 = last;
  int index = first1;
  while ((first1 <= last1) && (first2 <= last2)) {
    if (a[first1] < a[first2]) {
      temp[index] = a[first1];
      ++first1;
    } else {
      temp[index] = a[first2];
      ++first2;
    }
    ++index;
  }
  while (first1 <= last1) {
    temp[index] = a[first1];
    ++first1;
    ++index;
  }
  while (first2 <= last2) {
    temp[index] = a[first2];
    ++first2;
    ++index;
  }
  for (index = first; index <= last; ++index) {
    a[index] = temp[index];
  }  
}

/*
Destructor
*/
template <class T>
Merge_Sort<T>::~Merge_Sort()
{
}

/*
start_sort performs selection sort on the array and updates the observers as necessary
*/
template <class T>
int Merge_Sort<T>::start_sort()
{
  if (progress_ != Merge_Sort::NOT_STARTED) {
    cout << "Sort is either in progress or finished." << endl;
    return -1;
  }
  progress_ = Merge_Sort::STARTED;
  Timer t;
  if (mode_ == Merge_Sort::MERGE_SORT) {
    cout << "Merge Sort Start" << endl;
	t.start_time();
    MergeSort(array_data_, 0, array_data_.size() - 1);
	t.stop_time();
    cout << "Merge Sort Stop" << endl;
	cout << "Merge Sort Time" << endl;
	t.display_time();
  } else {
    cout << "Super Merge Start" << endl;
    t.start_time();
    Super_Merge();
	t.stop_time();
    cout << "Super Merge Stop" << endl;
	cout << "Super Merge Time" << endl;
	t.display_time();
  }
    Sort_Info<T> answer(Sort_Info_Base::MERGE_SORT, array_data_,
        Sort_Info_Base::SORTED);
    publish_sort_update(answer);
    progress_ = Merge_Sort::FINISHED;
  return 0;
}

/*
Super_Merge() merges the contents of the Array of Sort_Info<T>* and start_sort() publishes the results.
 */
template <class T>
void Merge_Sort<T>::Super_Merge()
{ 
  Array<T> temparray(0);
  for (int i = 0; i < Sort_Info_Array_.size(); i++) {
    Array<T> holder(Sort_Info_Array_[i]->data());
    if (Sort_Info_Array_[i]->status() != Sort_Info_Base::SORTED) {  
         Merge_Observer<T> mos(*this);
         Observer_Check_ = Merge_Sort::NO;
         Sorter *s = create_sorter(*Sort_Info_Array_[i]);
         s->register_observer(mos);
         s->start_sort();
         holder = temporary_holder_;
    }
    temparray = MergeTwoHelper(holder, temparray);
  }
  array_data_ = temparray;
}

/*
This is a helper that simply merges two arrays.
 */
template <class T>
Array<T> Merge_Sort<T>::MergeTwoHelper(Array<T> &s1,
  Array<T> &s2)
{
  Array<T> temp1 = s1;
  Array<T> temp2 = s2;
  Array<T> temp_array(temp1.size() + temp2.size());
  int index = 0;
  int index1 = 0;
  int index2 = 0;
  while(index1 < temp1.size() && index2 < temp2.size()) {
    if (temp1[index1] < temp2[index2]) {
      temp_array[index] = temp1[index1];
      ++index1;
    } else {
      temp_array[index] = temp2[index2];
      ++index2;
    }
    ++index;
  }
  while (index1 < temp1.size()) {
    temp_array[index] = temp1[index1];
    ++index1;
    ++index;
  }
  while (index2 < temp2.size()) {
    temp_array[index] = temp2[index2];
    ++index2;
    ++index;
  }  
  return temp_array;
}

/*
set_Observation is called by Update_Sort inside Merge_Observer.
 */
template <class T>
void Merge_Sort<T>::set_Observation(Array<T>& sort_observation_array_)
{
  temporary_holder_ = sort_observation_array_;
  Observer_Check_ = Merge_Sort::YES;
}

#endif
