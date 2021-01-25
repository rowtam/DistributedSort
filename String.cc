#ifndef STRING_C
#define STRING_C

#include "String.h"
#include <string.h>
#include <assert.h>

/*
Invariant 
strng_ = len + 1
len == strlen
*/

String::String() 
{
  this->len = 0;   
  strng_ = new char[1];
  if (strng_ == 0)
	assert(! "Terminating due to allocation failure");
  ::strcpy(strng_, "");
}

char* String::getbuf()
{
  return strng_;
}

String::~String() 
{
  delete [] strng_;
}

String::String(const char * str)
{ 
  this->len = ::strlen(str);
  strng_ = new char[len+1];
  if (strng_ == 0)
	assert(! "Terminating due to allocation failure");
  ::strcpy(strng_, str);
}

String::String(const String &s)
{  
  len = ::strlen(s.strng_);
  strng_ = new char[len+1];
  if (strng_ == 0)
	assert(! "Terminating due to allocation failure");
  ::strcpy(strng_, s.strng_);
}

String& String::operator= (const String &s)
{
  if (strng_ != 0)
    delete [] strng_;
  strng_ = new char[s.length() + 1];
  if (strng_ == 0)
	assert(! "Terminating due to allocation failure");
  ::strcpy(strng_, s.strng_);
  this->len = s.length();
  return *this;
}

int String::operator== (const String &s) const
{
  return (::strcmp(s.strng_, strng_) == 0);
}

int String::operator!= (const String &s) const
{
  return !(s.strng_ == strng_);
}

int String::operator< (const String &s) const
{
  return (::strcmp(strng_, s.strng_) < 0);
}

int String::operator<= (const String &s) const
{
  int temp = ::strcmp(strng_, s.strng_);
  return (temp < 0 || temp == 0);
}

int String::operator> (const String &s) const
{
  return (::strcmp(strng_, s.strng_) > 0);
}

int String::operator>= (const String &s) const
{
  int temp = ::strcmp(strng_, s.strng_);
  return (temp > 0 || temp == 0);
}

istream &operator>> (istream& is, String &s)
{
  char t[255];
  is.getline(t, 255);
  int size = ::strlen(t);
  if (s.length() < size) {
	delete [] s.strng_;
        s.strng_ = new char[size + 1];
	assert(s.strng_ != 0);
  }
  ::strcpy(s.strng_, t);
  s.length(size);
  return is;
}


ostream &operator<< (ostream& os, const String &s)
{
  os << s.strng_;
  return os;
}
#endif /* STRING_C */
