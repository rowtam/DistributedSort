#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Sorter.h"
#include "Sort_Viewer_Client.h"

template <class T>
class Merge_Sort : public Sorter
{
  // = TITLE
  //     Selection_Sort
  //
  // = DESCRIPTION
  //     Extends Sorter to provide the Sort algorithm.
public:
  // Manager functions.

  Merge_Sort (const Sort_Info<T> &s);
  Merge_Sort (const Array<Sort_Info<T>*> &s);

  virtual ~Merge_Sort ();

  // Implementor functions.

  virtual int start_sort ();
  // Starts the sort operation.  Returns 0 on success,
  // or -1 if the start had already been started.

  // You fill in here . . .
    
  enum Progress {
	NOT_STARTED, 
	STARTED, 
	FINISHED};

  Progress progress_;

  enum VIEWER_STATUS {
        JAVA_VIEWER_DETECTED,
	JAVA_VIEWER_NOT_DETECTED 
  };
  
  VIEWER_STATUS viewer_status_;
  
  enum sort_mode {
  	MERGE_SORT,
  	SUPER_MERGE
  };

  enum Observation_Returned {
    YES,
    NO
  };

  Observation_Returned Observer_Check_;
  
  void set_Observation(Array<T>&);

  Array<T> temporary_holder_;
  
  sort_mode mode_;
/*
  int get_data(Sort_Info<T>& s) {
    if (progress_ == Merge_Sort::FINISHED && mode_ ==
	Merge_Sort::MERGE_SORT) {
      s = Sorted_data_;
      return 0;
    } else
      return -1;
  }             
*/
private:
//  Sort_Info<T> Sorted_data_;  

  void Super_Merge();

  void MergeSort(Array<T>& a, int first, int last);

  void Merge(Array<T>& a, int first, int mid, int last);

  Array<T> array_data_;

  Array<Sort_Info<T>*> Sort_Info_Array_;

//  int getsize();

  Array<T> MergeTwoHelper(Array<T> &s1, Array<T> &s2);  

};

#if defined (__GNUG__) || defined (__MWERKS__) || defined (_VCPP_) || \
    defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  // For explicit template instantiation, the definitions must be
  // visible to the compiler.
# include "Merge_Sort.cc"
#endif /* EXPLICIT_TEMPLATE_INSTANTIATION */

#endif /* MERGE_SORT_H */
