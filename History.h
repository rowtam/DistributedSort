#ifndef HISTORY_H
#define HISTORY_H

// $Id: History.h,v 1.3 2000/02/11 17:00:48 cs342 Exp $
//
// History.h - header file for History class
// copyright, 1997, Stan C. Kwasny
// Copyright 1999, David L. Levine
//
// ChangeLog:
// 20 Sep 1999, David L. Levine: redesiged so that it's used as a base
//              class.  Thanks to Adam Lopresto for suggesting this,
//              and to Evan Jeffrey and Adam Smith for helping with the design.
// 28 Jan 1999, Evan Jeffrey: added report () call to destructor.
// 27 Jan 1999, David L. Levine:  added documentation, and captialized History.
// 14 Jan 1999, David L. Levine:  added enable/disable_debug ().
// 14 Jan 1999, David L. Levine:  moved #includes to .cc file.
// 12 Jan 1999, Luther Baker: (destroy_item): moved assert to after the
//              printout.

template <class T, const char NAME[]>
class History;


template <class T, const char NAME[]>
class History_Final_Report
{
  // = TITLE
  //     Causes a final History report to be generated at program
  //     termination.
  //
  // = DESCRIPTION
  //     For internal use by template class History, only.
public:
  // egcs 1.0.3 needs the destructor to be public.
  ~History_Final_Report ();
  // Issues final report for corresponding History<T, NAME> class.

private:
  History_Final_Report ();
  // Sun CC needs the explicit constructor to ensure that the
  // static object is constructed and destructed.

  void enable_report ();
  // No-op function, for History <T, NAME> constructor to use the
  // static instance.  Must be non-inline for success with DEC cxx.

  friend class History<T, NAME>;
};


template <class T, const char NAME[]>
class History
{
  // = TITLE
  //     Instruments a user-defined class to record
  //     constructions/destructions.
  //
  // = DESCRIPTION
  // The history class keeps track of 1) the number of constructor calls
  // and 2) the number of destructor calls, for an instrumented class.
  // At any time, it can report:
  //   1) how many times the constructors have been called,
  //   2) the maximum number of objects of the instrumented class in use
  //      during the entire program run, and
  //   3) the number of objects in use when the report () method is call.
  //
  // The report () method is called at program termination, unless the
  // HISTORY_FINAL_REPORT environment variable is set to 0.  If it reports
  // that some objects are in use, that indicates a memory leak.
  //
  // To use, all you need to do is derive the class that you want to
  // instrument from the History template class.  By way of example,
  // to instrument a template class:
  //   in Foo.h:
  //     #include "History.h"
  //
  //     extern const char Foo_Name[];
  //
  //     template <class T>
  //     class Foo : virtual public History<Foo<T>, Foo_Name>
  //     {
  //     [...]
  //
  //   in Foo.cc:
  //     #include "Foo.h"
  //
  //     const char Foo_Name[] = "Foo<T>";
  //
  // For templates classes, History will then report using the formal
  // template instantiation parameters by default.  To use the actual
  // parameters, add a call to the static name () function, in your
  // code, e.g.,
  //   History<Foo<long>, Foo_Name>::name ("Foo<long>");
  // (Older versions of g++ won't be able compile that, though.)
  //
  // The debug option, if enabled, causes a printout to stderr for each
  // constructor and destructor call.
  //
  // These environment variables are supported at run time:
  //    HISTORY_ASSERT: if set to 0, reports excessive destructor calls
  //                    with an error message instead of assert ().
  //    HISTORY_DEBUG:  if set, enables debug (same as enable_debug ()).
  //    HISTORY_FINAL_REPORT: if not set to 0, report () is called at
  //                          program termination.
  //
public:
  History ();

  virtual ~History ();

  static void report ();
  // Print report to stderr.

  static void enable_debug () { debug_ = 1; }
  // Enable debug printouts in constructor/destructor.

  static void disable_debug () { debug_ = 0; }
  // Disable debug printouts in constructor/destructor.

  static const char *name ();
  // Access the History name.

  static void name (const char *class_name) { name_ = class_name; }
  // Set the History name, overriding the NAME template parameter.

private:
  unsigned int id_;
  // Unique instance identifier.

  static History_Final_Report<T, NAME> final_report_;
  // Static instance causes final report to be issued at program
  // termination.

  static unsigned int name_count_;
  // How many instances have been constructed.

  static unsigned int max_count_;
  // Maximum number of instances in existence at any point in time.

  static unsigned int in_use_count_;
  // Number of instances currently in use.

  static unsigned int debug_;
  // Debug enabled/disabled flag.

  static const char *name_;
  // The class name:  allows overriding of NAME at runtime.
};

#if defined (__GNUG__) || defined (__MWERKS__) || defined (_VCPP_) || \
    defined (EXPLICIT_TEMPLATE_INSTANTIATION)
  // Necessary for template instantiation with some compilers.
# include "History.cc"
#endif /* EXPLICIT_TEMPLATE_INSTANTIATION */

#endif
