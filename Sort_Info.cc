// $Id: Sort_Info.cc,v 1.3 2000/03/13 19:18:26 cs342 Exp $

#ifndef SORT_INFO_CC
#define SORT_INFO_CC

#include "Sort_Info.h"

/*
Constructor explicitly calls the parent constructor and 
initialized the Array<T> data_
*/
template <class T>
Sort_Info<T>::Sort_Info (const Sort_Type sort_type, const Array<T> &data,
const Status stat)
  :Sort_Info_Base(sort_type, stat),
   data_(data)
{
}

/*
An additional constructor that simply takes in an istream and reads in the
data for the sort_info.

This isn't really needed (or used currently), but it might be useful in
the future, and Andrew Gilpin suggested it as an idea.

*/
template <class T>
Sort_Info<T>::Sort_Info (istream& is)
{
  this->read(is);
}

template <class T>
Sort_Info<T>::Sort_Info (const Sort_Type sort_type, const char* filename,
const Status stat)
  :Sort_Info_Base(sort_type, stat)
{
  this->readFile(filename);
}

template <class T>
Sort_Info<T>::Sort_Info (istream& is, const int n)
{
  this->readCompleteStringStream(is);
  int k = n;
}  

/*
destructor
*/
template <class T>
Sort_Info<T>::~Sort_Info()
{
}

/*
print, calls the base print method which prints out sort_type and status.  Then, this
method prints out the array data.
*/
template <class T>
void Sort_Info<T>::print (ostream &os) const
{
  Sort_Info_Base::print (os);
  os << data_.size() << endl;
  for(int i = 0; i < data_.size(); i++) {
    os << data_[i] << endl;
  }  
}

/*
read is fully compatible with print and reads in input
from an istream.  
*/
template <class T>
void Sort_Info<T>::read (istream &is)
{
  Sort_Info_Base::read (is);
  int tempsize;
  is >> tempsize;
  data_ = Array<T>(tempsize);
  for (int i = 0; i < tempsize; i++) {
    is >> data_[i];
  }  
}

template <class T>
void Sort_Info<T>::readCompleteStringStream(istream& is)
{
  Sort_Info_Base::read(is);
  char buf[255];
  int tempsize;
  is >> tempsize;
  is.getline(buf,255);  // consume the line feed;
  data_ = Array<T>(tempsize);
  for(int l = 0; l < tempsize && !is.eof(); ++l) {
    is >> data_[l];
  }                       
}

template <class T>
void Sort_Info<T>::readFile(const char* filename)
{
  ifstream ifstr(filename);
  char buf[255];
  for(int k = 0; !ifstr.eof(); ++k) {
    ifstr.getline(buf, 255);
  }
  data_ = Array<T>(k);
  ifstream ifstr2(filename);
  for (int j = 0; !ifstr2.eof(); ++j) {
    ifstr2 >> data_[j]; 
  } 
  
}

/*
shift operator
*/
template <class T>
ostream &operator<< (ostream &os, const Sort_Info<T> &si)
{
  si.print(os);
  return os;
}

/*
shift operator
*/
template <class T>
istream &operator>> (istream &is, Sort_Info<T> &si)
{
  si.read(is);
  return is;
}

#endif /* SORT_INFO_CC */
