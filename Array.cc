// $Id: Array.cc,v 1.4 2000/01/23 15:36:32 cs342 Exp $

#ifndef ARRAY_C
#define ARRAY_C

#include "Array.h"
#include <iostream.h>
#include <assert.h>

// If you want to use std::nothrow:
// #include <new>  /* for new (std::nothrow) */


// Copy constructor.
template <class T>
Array<T>::Array (const Array<T> &s)
  : max_size_ (s.size ()),
    cur_size_ (s.size ()),
    array_ (0)
{
  if (max_size_ > 0) {
    array_ = new T[s.size ()];

    if (array_ == 0) {
      cerr << "Array<T>::Array; allocation of "
           << s.size ()
           << " elements failed!"
           << endl;

      max_size_ = cur_size_ = 0;

      assert (! "Terminating program");
    } else {
      for (size_t i = 0; i < size (); i++) {
        array_[i] = s.array_[i];
      }
    }
  }
}

// Dynamically create an uninitialized array.  It's dynamically   
// created so that we can determine the size at run-time, instead of
// compile time.

template <class T>
Array<T>::Array (size_t size)
  : max_size_ (size),
    cur_size_ (size)
{
  array_ = new T[size];		// allocate a new array of T
  if (array_ == 0) {		// check for successful allocation
    cerr << "Array<T>::Array(size_t size);\n" 
         << "Allocation of "
         << size
         << "elements failed!" << endl;
    assert (! "Terminating program"); 
  }
}   

// Dynamically create and initialize the entire array to the
// default_value.  It's dynamically created so that we can determine
// the size at run-time, instead of compile time.
 
template <class T>
Array<T>::Array (size_t size, const T &default_value)
  : max_size_ (size),
    cur_size_ (size)
{
  array_ = new T[size];		// allocate a new array
  if (array_ == 0) {		// check for successful allocation
    cerr << "Array<T>::Array(size_t size, const T &default_value);\n"
         << "Allocation of "  
         << size
         << "elements failed!" << endl;
    assert (! "Terminating program");
  } else {
    for (size_t i = 0; i < size; i++) {	// initialize array to default
      array_[i] = default_value;          // value
    }
  }
}

// Assignment operator performs an assignment by making an exact
// copy of the contents of parameter s, so that *this == s will
// be true.  Note that if the max_size_ of array_ is >= than
// s.cur_size_ we can copy it without reallocating.  However, if
// max_size_ is < s.cur_size_ we must delete the array_,
// reallocate a new array_, and then copy the contents of s.
  
template <class T>
Array<T>& Array<T>::operator= (const Array<T> &s)
{
  if (this != &s) {			// Check for self-assignment
    if (max_size_ < s.max_size_) {  // check if reallocation needed
      delete []array_;			// deallocate
      array_ = new T[s.size()];	// reallocate the array
      cur_size_ = s.cur_size_;
      max_size_ = s.max_size_;
      if (array_ == 0) {		// check for successful allocation
        cerr << "Array<T> assignment operator reallocation;\n"
           << "Allocation of "
           << size()
           << "elements failed!" << endl;
        assert (! "Terminating program");
      }
    }
    cur_size_ = s.cur_size_;
    max_size_ = s.max_size_;
    for (size_t i=0; i < s.size(); i++) {	// copy elements over
      array_[i] = s.array_[i];		// to array
    }
    return *this;					// return this
  }
  cout << "\n Self-assignment detected by assignment operator"
       << " method.\n" << endl;
  return *this;
}

// Clean up the array, e.g., delete dynamically allocated memory.

template <class T>
Array<T>::~Array ()
{
  delete []array_;	// destructor
} 

// Set an item in the array at location index.  Returns 0 on
// success, or -1 if index is not in_range.

template <class T>
int Array<T>::set (size_t index, const T &new_item) 
{
  if (in_range(index) == 0) {
    return -1;
  } else {
    array_[index] = new_item;
  }
  return 0;
}

// Copies the array value at location index to the item argument,   
// which is passed by value.  Returns 0 on success, or -1 if index
// is not in_range (in which case item is not modified).

template <class T>
int Array<T>::get (size_t index, T &item) const
{
  if (in_range(index) == 0) {
    return -1;
  } else {                 
    item = array_[index];
  }
  return 0;  
}

// Overloaded operator[] to set.

template <class T>
T &Array<T>::operator[] (const size_t index)
{
  if (in_range(index) == 0) {
    cerr << "Call to set [] operator with out of bounds index:"
         << index << "\n" << endl;
    assert(! "Terminating program -> Index Out Of Bounds");
  } else {
    return array_[index];	
  }
}

// Overloaded operator[] to get.

template <class T>
const T &Array<T>::operator[] (const size_t index) const
{
  if (!in_range(index)) {
    cerr << "\nCall the get [] function with out of bounds index:" 
         << index << " \n" << endl;
    assert(! "Terminating program -> Index Out Of Bounds");
  } else {
    return array_[index];
  }
}

// Returns the cur_size_ of the array.

template <class T>
size_t Array<T>::size () const
{
  return cur_size_;
}

// Compare this array with s for equality.  Two arrays are equal
// if their size()'s are equal and all the elements from 0 .. size()
// are equal.  Returns 1 if the arrays are equal, 0 if not equal.

template <class T>
int Array<T>::operator== (const Array<T> &s) const
{
  if(this == &s)		// check if we are comparing to self
    return 1;
  if (s.size() == size()) {	// check size and elements
    for (int i = 0; i < size(); i++) {
      if (s.array_[i] != array_[i])
        return 0;
    }
    return 1;
  }
  return 0;
}

// Compare this array with s for inequality such that *this != s
// is always the complement of the return value of *this == s.  

template <class T>
int Array<T>::operator!= (const Array<T> &s) const
{
  return !(*this == s);
}

// Returns 1 if index is within range, i.e., 0 <= index < cur_size_,
// else returns 0.

template <class T>
int Array<T>::in_range (size_t index) const
{
  if (index >= 0 && index < max_size_)
    return 1;
  else
    return 0;

}

#endif /* ARRAY_C */
