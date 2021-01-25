#ifndef DISTRIBUTED_SORT_H
#define DISTRIBUTED_SORT_H

#include "Sorter.h"
#include "Sort_Viewer_Client.h"
#include "Connector.h"
#include "Distributed_Sort_Observer.h"

template <class T>
class Distributed_Sort : public Sorter
{
  // = TITLE
  //     Distributed_Sort
  //
  // = DESCRIPTION
  //     Extends Sorter to provide the Sort algorithm.
public:
  // Manager functions.

  Distributed_Sort (const Sort_Info<T> &s);

  virtual ~Distributed_Sort ();

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
  void set_Observation(Array<T>&);

private:
  Array<T> Observation;
  Array<Connector<T>*> connectors;
  int partition_size;
  int numIPs;
};

#if defined (__GNUG__) || defined (__MWERKS__) || defined (_VCPP_) || \
    defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  // For explicit template instantiation, the definitions must be
  // visible to the compiler.
# include "Distributed_Sort.cc"
#endif /* EXPLICIT_TEMPLATE_INSTANTIATION */

#endif /* DISTRIBUTED_SORT_H */
