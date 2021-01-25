/* -*- C++ -*- */
// $Id: Sorter.h,v 1.2 2000/03/13 05:32:39 cs342 Exp $

#ifndef SORTER_H
#define SORTER_H

#include "Sort_Info.h"    /* For convenience of clients. */
#include "Array.h"

#include "Sort_Observer.h"
//class Sort_Observer;


class Sorter
{
  // = TITLE
  //     Sorter
  //
  // = DESCRIPTION
  //     Accepts sort requests, and provides sort results to
  //     registered observers.
public:
  // Manager functions.

  virtual ~Sorter ();

  // Implementor functions, for use by Sorter clients.
  int register_observer (Sort_Observer &sort_observer);
  // Register an observer for the sort.  Returns 0 on success,
  // -1 on failure (reached maximum number of observers).

  virtual int start_sort () = 0;
  // Starts the sort operation.  Returns 0 on success,
  // or -1 if the sort had already been started.

  static unsigned int maximum_observers ();
  // Returns the maximum number of observers per Sorter.

protected:
  // Manager functions, for use by Sort algorithms.
  Sorter ();

  // Implementor functions, for use by Sort algorithms.
  void publish_sort_update (const Sort_Info_Base &sort_observation);
  // Used by Sort algorithms to publish updates on Sort status
  // to registered observers.

private:
  // Helper functions.
  // For use by register_observer () . . .
  int set_observer (unsigned int i, Sort_Observer *sort_observer);
  // Set the i'th Sort_Observer.  Returns 0 on success, -1 if
  // i is greater than the observers_ Array size.

  // For use by publish_sort_update () . . .
  Sort_Observer *get_observer (unsigned int i);
  // Access the i'th Sort_Observer.

  Array<Sort_Observer *> observers_;
  // Array of Sort_Observers.

  unsigned int num_observers_;
  // Number of registered observers.
};

template <class T>
Sorter *
create_sorter (const Sort_Info<T> &sort_info);
// Factory Method for creating a Sorter.

#endif /* SORTER_H */
