// $Id: Array.h,v 1.4 2000/01/24 23:11:34 cs342 Exp $

#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>  /* For size_t. */
/* NOTE:  size_t is an integral type that is appropriate for
   array indices.  It is a typedef of another integral type,
   but which one is platform dependent. */

// This will be an array of T, i.e., it is a parameterized type.

template <class T>
class Array
{
public:
  // Define a "trait"
  typedef T TYPE;

  // = Initialization and termination methods.

  Array (size_t size = 0);
  // Dynamically create an uninitialized array.  It's dynamically
  // created so that we can determine the size at run-time, instead of
  // compile time.

  Array (size_t size, const T &default_value);
  // Dynamically create and initialize the entire array to the
  // default_value.  It's dynamically created so that we can determine
  // the size at run-time, instead of compile time.

  Array (const Array<T> &s);
  // The copy constructor performs initialization by making an exact
  // copy of the contents of parameter s, so that *this == s will
  // be true.

  Array<T> &operator= (const Array<T> &s);
  // Assignment operator performs an assignment by making an exact
  // copy of the contents of parameter s, so that *this == s will
  // be true.  Note that if the max_size_ of array_ is >= than
  // s.cur_size_ we can copy it without reallocating.  However, if
  // max_size_ is < s.cur_size_ we must delete the array_,
  // reallocate a new array_, and then copy the contents of s.

  ~Array ();
  // Clean up the array, e.g., delete dynamically allocated memory.

  // = Set/get methods.

  int set (size_t index, const T &new_item);
  // Set an item in the array at location index.  Returns 0 on
  // success, or -1 if index is not in_range.

  int get (size_t index, T &item) const;
  // Copies the array value at location index to the item argument,
  // which is passed by value.  Returns 0 on success, or -1 if index
  // is not in_range (in which case item is not modified).

  T &operator[] (const size_t index);
  // Overloaded operator[] to set.  Note that the index is not checked
  // for in range!  (You can implement using set () and ignore the
  // return value.)

  const T &operator[] (const size_t index) const;
  // Overloaded operator[] to get.  Note that the index is not checked
  // for in range!  (You can implement using get () and ignore the
  // return value.)

  size_t size () const;
  // Returns the cur_size_ of the array.

  int operator== (const Array<T> &s) const;
  // Compare this array with s for equality.  Two arrays are equal
  // if their size()'s are equal and all the elements from 0 .. size()
  // are equal.  Returns 1 if the arrays are equal, 0 if not equal.

  int operator!= (const Array<T> &s) const;
  // Compare this array with s for inequality such that *this != s
  // is always the complement of the return value of *this == s.

private:
  // = Helper method.

  int in_range (size_t index) const;
  // Returns 1 if index is within range, i.e., 0 <= index < cur_size_,
  // else returns 0.

  // = Data members (instance variables).

  size_t max_size_;
  // Maximum size of the array, i.e., the total number of T elements
  // in array_.  Note that max_size_ is only used when assigning
  // one array to another, to avoid reallocating when it's not necessary.

  size_t cur_size_;
  // Current size of the array.  This starts out being == to
  // max_size_.  However, if we are assigned a smaller array, then
  // cur_size_ will become less than max_size_.  The purpose of
  // keeping track of both sizes is to avoid reallocating memory if we
  // don't have to.

  T *array_;
  // Pointer to the array's storage buffer.
};

#if defined (__GNUG__) || defined (__MWERKS__) || defined (_VCPP_) \
    || defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  // For explicit template instantiation with some compilers.
# include "Array.cc"
#endif /* __GNUG__ || __MWERKS__|| EXPLICIT_TEMPLATE_INSTANTIATION */

#endif /* ARRAY_H */
