/* -*- C++ -*- */
// $Id: Sort_Info_Base.h,v 1.4 2000/03/13 19:28:58 cs342 Exp $

#ifndef SORT_INFO_BASE_H
#define SORT_INFO_BASE_H

#include "History.h"
#include <iostream.h>
#include <string.h>

extern const char Sort_Info_Base_Name[];
class Sort_Info_Base : virtual public History<Sort_Info_Base,
                                              Sort_Info_Base_Name>
{
  // = TITLE
  //     Sort_Info_Base
  //
  // = DESCRIPTION
  //     Non-template base class for Sort_Info template classes.
public:
  enum Status { UNSORTED, PARTIALLY_SORTED, SORTED };

  enum Sort_Type {
    ANY_SORT,  // Allows Sorter to select the sort algorithm.
    SELECTION_SORT,
    MERGE_SORT,
    QUICK_SORT,
    DISTRIBUTED_SORT
  };

  // Accessor functions.
  Sort_Type sort_type () const { return sort_type_; }
  void sort_type (Sort_Type new_sort_type) { sort_type_ = new_sort_type; }

  Status status () const { return status_; }
  void status (Status new_status) { status_ = new_status; }

  // Implementor functions.
  virtual void print (ostream &) const = 0;
  // Output the contents to the specified stream.  Note that it
  // is pure virtual, but can still have an implementation in this
  // base class.

  virtual void read (istream &) = 0;
  // Read the object from the stream.  Note that it is pure
  // virtual, but can still have an implementation in this
  // base class.

protected:
  // Manager methods.
  Sort_Info_Base (const Sort_Type sort_type = ANY_SORT,
                  const Status status = UNSORTED);
  virtual ~Sort_Info_Base ();

private:
  Sort_Type sort_type_;
  // The type of sort requested.

  Status status_;
  // The current status of the sort.

  // Hidden methods which are not implemented:
  Sort_Info_Base (const Sort_Info_Base &);
  Sort_Info_Base &operator= (const Sort_Info_Base &);
};

ostream &operator<< (ostream &, const Sort_Info_Base &);

istream &operator>> (istream &, Sort_Info_Base &);

#endif /* SORT_INFO_BASE_H */
