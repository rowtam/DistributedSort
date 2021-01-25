// $Id: History.cc,v 1.1 1999/09/26 04:10:28 cs342 Exp $
//
// History.cc - implementation file for History class
// copyright, 1997, Stan C. Kwasny
// Copyright 1999, David L. Levine
// See History.h for ChangeLog.

#include "History.h"

#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

template <class T, const char NAME[]>
History_Final_Report<T, NAME>
History<T, NAME>::final_report_;

template <class T, const char NAME[]>
unsigned int
History<T, NAME>::name_count_ = 0;

template <class T, const char NAME[]>
unsigned int
History<T, NAME>::max_count_ = 0;

template <class T, const char NAME[]>
unsigned int
History<T, NAME>::in_use_count_ = 0;

template <class T, const char NAME[]>
unsigned int
History<T, NAME>::debug_ = 0;

template <class T, const char NAME[]>
const char *
History<T, NAME>::name_= 0;

template <class T, const char NAME[]>
History_Final_Report<T, NAME>::~History_Final_Report ()
{
  const char *const final_report = ::getenv ("HISTORY_FINAL_REPORT");
  if (! (final_report  &&  ! ::strcmp (final_report, "0"))) {
    History<T, NAME>::report ();
  }
}

template <class T, const char NAME[]>
History_Final_Report<T, NAME>::History_Final_Report ()
{
}

template <class T, const char NAME[]>
void
History_Final_Report<T, NAME>::enable_report ()
{
}

template <class T, const char NAME[]>
History<T, NAME>::History ()
  : id_ (++name_count_)
{
  ++in_use_count_;
  if (in_use_count_ > max_count_) {
    max_count_ = in_use_count_;
  }

  final_report_.enable_report ();

  if (debug_  ||  ::getenv ("HISTORY_DEBUG")) {
    cerr << "==> CREATING   " << name ()
         << " # " << id_
         << "; count = " << name_count_
         << "; max = " << max_count_
         << "; in use = " << in_use_count_
         << " <==" << endl;
  };
}

template <class T, const char NAME[]>
History<T, NAME>::~History ()
{
  if (debug_  ||  ::getenv ("HISTORY_DEBUG")) {
    cerr << "==> DESTROYING " << name ()
         << " # " << id_
         << "; count = " << name_count_
         << "; max = " << max_count_
         << "; in use = " << in_use_count_ - 1
         << " <==" << endl;
  };

  if (in_use_count_ == 0) {
    const char *const history_assert = ::getenv ("HISTORY_ASSERT");
    if (history_assert  &&  ! ::strcmp (history_assert, "0")) {
      cerr << "====> in_use_count_ for \"" << name()
           << "\" is 0, and will be decremented!!!!\n";
    } else {
      assert (in_use_count_ > 0);
    }
  }

  --in_use_count_;
}

template <class T, const char NAME[]>
const char *History<T, NAME>::name ()
{
  return name_  ?  name_  :  NAME;
}

template <class T, const char NAME[]>
void
History<T, NAME>::report()         // Tell all
{
  cerr << endl;
  cerr << "================ HISTORY REPORT =================" << endl;
  cerr << "  \"" << name () << "\" total constructed = " << name_count_
       << endl;
  cerr << "  \"" << name () << "\" peak in use       = " << max_count_ << endl;
  cerr << "  \"" << name () << "\" now in use        = " << in_use_count_
       << endl;
  cerr << "=================================================" << endl;
}
