/* -*- C++ -*- */
// $Id: Sort_Info.h,v 1.4 2000/03/13 19:28:58 cs342 Exp $

#ifndef SORT_INFO_H
#define SORT_INFO_H

#include "Sort_Info_Base.h"
#include <stdlib.h>  // for atoi function
#include "Array.h"

template <class T>
class Sort_Info : public Sort_Info_Base
{
  // = TITLE
  //     Sort_Info
  //
  // = DESCRIPTION
  //     Adds data, of type T, to Sort_Info_Base.
public:
  // Manager functions.
  Sort_Info (const Sort_Type sort_type,
             const Array<T> &data,
             const Status status = UNSORTED);
  // Constructor.  Copies the data to an internal Array.
  
  Sort_Info (istream& is);

  Sort_Info (const Sort_Type sort_type,
	     const char * filename,
             const Status stat);

  Sort_Info (istream& is, const int n);

  virtual ~Sort_Info ();

  // Implementor functions.
  virtual void print (ostream &) const;
  // Output the contents to the specified stream.

  virtual void read (istream &);
  // Read the object from the stream.  Must be compatible with
  // print (ostream &).

  // Accessor functions.
  const Array<T> &data () const { return data_; }
  Array<T> &data () { return data_; }
  
  void readCompleteStringStream(istream &is);
  void readFile(const char * filename);
  void printStringStream(ostream& os) const;
private:
  Array<T> data_;
  // Elements to be sorted.

  // Hidden methods which are not implemented, to force instantiation
  // with parameters.
  Sort_Info ();
  Sort_Info (const Sort_Info &);
  Sort_Info &operator= (const Sort_Info &);
  
  friend ostream &operator<< (ostream &, const Sort_Info<T> &);
  friend istream &operator>> (istream &, Sort_Info<T> &);
};

template <class T>
ostream &operator<< (ostream &, const Sort_Info<T> &);

template <class T>
istream &operator>> (istream &, Sort_Info<T> &);

#if defined (__GNUG__) || defined (__MWERKS__) || defined (_VCPP_) || \
    defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  // For explicit template instantiation, the definitions must be
  // visible to the compiler.
# include "Sort_Info.cc"
#endif /* EXPLICIT_TEMPLATE_INSTANTIATION */

#endif /* SORT_INFO_H */
