/* -*- C++ -*- */
// $Id: Sort_Observer.h,v 1.2 2000/03/13 05:32:39 cs342 Exp $

#ifndef SORT_OBSERVER_H
#define SORT_OBSERVER_H

#include "Sort_Info.h"  /* For convenience of clients, instead of
                           Sort_Info_Base.h */

class Sort_Observer
{
  // = TITLE
  //     Sort_Observer
  //
  // = DESCRIPTION
  //     Abstract Sort_Observer base class.
public:
  // Manager function.
  virtual ~Sort_Observer ();

  // Implementor functions.
  virtual void update_sort (const Sort_Info_Base &sort_info) = 0;
  // Callback, to receive a sort observation.
};

#endif /* SORT_OBSERVER_H */
