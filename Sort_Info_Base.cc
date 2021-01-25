// $Id: Sort_Info_Base.cc,v 1.3 2000/03/13 19:18:26 cs342 Exp $

#include "Sort_Info_Base.h"

const char Sort_Info_Base_Name[] = "Sort_Info_Base";

/*
Initialize sort_type_ and status_
*/
Sort_Info_Base::Sort_Info_Base (const Sort_Type sort_type, 
   const Status stat)
   :sort_type_(sort_type),
    status_(stat)
{
}

/*
destructor
*/
Sort_Info_Base::~Sort_Info_Base()
{
}

/*
read reads in sort_type and status
*/
void Sort_Info_Base::read (istream &is)
{
  char bufsort[32];
  is >> bufsort;
  if (! ::strcmp(bufsort, "SELECTION_SORT"))
    sort_type(Sort_Info_Base::SELECTION_SORT);
  else if (! ::strcmp(bufsort, "MERGE_SORT"))
    sort_type(Sort_Info_Base::MERGE_SORT);
  else if (! ::strcmp(bufsort, "QUICK_SORT"))
    sort_type(Sort_Info_Base::QUICK_SORT);
  else
    sort_type(Sort_Info_Base::ANY_SORT);
  char buf[32];
  is >> buf;
  if (! ::strcmp(buf, "SORTED"))
    status(Sort_Info_Base::SORTED);
  else if (! :: strcmp(buf, "PARTIALLY_SORTED"))
    status(Sort_Info_Base::PARTIALLY_SORTED);
  else
    status(Sort_Info_Base::UNSORTED);
  
  
}

/*
print prints sort_type and status
*/
void Sort_Info_Base::print (ostream &os) const
{
 switch(sort_type()) {
    case Sort_Info_Base::ANY_SORT :
      os << "ANY_SORT" << endl;
      break;
    case Sort_Info_Base::SELECTION_SORT :
      os << "SELECTION_SORT" << endl;
      break;
    case Sort_Info_Base::MERGE_SORT :
      os << "MERGE_SORT" << endl;
      break;
    case Sort_Info_Base::QUICK_SORT :
      os << "QUICK_SORT" << endl;
      break;
  }
  switch(status()) {
    case Sort_Info_Base::UNSORTED :
      os << "UNSORTED" << endl; 
      break;
    case Sort_Info_Base::PARTIALLY_SORTED :
      os << "PARTIALLY_SORTED" << endl;
      break;
    case Sort_Info_Base::SORTED :
      os << "SORTED" << endl;
      break; 
  }  
}

/*
shift operator
*/
ostream &
operator<< (ostream &os, const Sort_Info_Base &sib)
{
  sib.print (os);
  return os;
}

/*
shift operator
*/
istream &
operator>> (istream &is, Sort_Info_Base &sib)
{
  sib.read (is);
  return is;
}
