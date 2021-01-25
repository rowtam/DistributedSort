#ifndef STRING_H
#define STRING_H

#include <iostream.h>

class String 
{

 public:
  char * strng_;  // character buffer 
  String();
  ~String();
  String(const char *);
  String(const String&);
  char* getbuf();
  String &operator= (const String&);
  int operator== (const String&) const;
  int operator!= (const String&) const;
  int operator< (const String&) const;
  int operator> (const String&) const;
  int operator>= (const String&) const;
  int operator<= (const String&) const;
  int length() const {return len;};
  void length(int t) {len = t;}; 
  //friend function
  friend ostream & operator<<(ostream&, const String &);
  friend istream & operator>>(istream&, String&); 
 private:
  int len;
};

istream& operator>> (istream&, String &);

ostream& operator<< (ostream&, const String &);

#endif /* STRING_H */
