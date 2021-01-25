#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "Sorter.h"
#include "Sort_Viewer_Client.h"

template <class T>
class Quick_Sort : public Sorter
{
  // = TITLE
  //     Quick_Sort
  //
  // = DESCRIPTION
  //     Extends Sorter to provide the Sort algorithm.
public:
  // Manager functions.

  Quick_Sort (const Sort_Info<T> &s);

  virtual ~Quick_Sort ();

  // Implementor functions.

  virtual int start_sort ();
  // Starts the sort operation.  Returns 0 on success,
  // or -1 if the start had already been started.

  // You fill in here . . .
  Array<T> array_data_;
  
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

/*
  int get_data(Sort_Info<T>& s) {
    if (progress_ == Quick_Sort::FINISHED) {
      s = Sorted_data_;
      return 0;
    } else
      return -1;
  }
*/

private:
  void QSort(Array<T>& a, int first, int last);
  int Partition(Array<T>& a, int first, int last); 
//  Sort_Info<T> Sorted_data_;
  
};

#if defined (__GNUG__) || defined (__MWERKS__) || defined (_VCPP_) || \
    defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  // For explicit template instantiation, the definitions must be
  // visible to the compiler.
# include "Quick_Sort.cc"
#endif /* EXPLICIT_TEMPLATE_INSTANTIATION */

#endif /* QUICK_SORT_H */
