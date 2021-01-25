// $Id: create_sorter.cc,v 1.2 2000/03/13 05:32:39 cs342 Exp $
//
// create_sorter Factory

#include "Sorter.h"
#include "Sort_Info.h"
#include "Selection_Sort.h"
#include "Merge_Sort.h"
#include "Quick_Sort.h"
#include "Distributed_Sort.h"
#include <iostream.h>

template <class T>
Sorter *
create_sorter (const Sort_Info<T> &sort_info)
{
  switch (sort_info.sort_type ()) {
    case Sort_Info_Base::ANY_SORT :
    case Sort_Info_Base::SELECTION_SORT : {
      return new Selection_Sort<T> (sort_info);
    }
    case Sort_Info_Base::QUICK_SORT : {
      return new Quick_Sort<T> (sort_info);
    }
    case Sort_Info_Base::MERGE_SORT : {
      return new Merge_Sort<T> (sort_info);
    }
    case Sort_Info_Base::DISTRIBUTED_SORT : {
      return new Distributed_Sort<T> (sort_info);
    }
    default :
      cerr << "create_sorter (): ERROR; unsupported SORT_TYPE: "
           << (int) sort_info.sort_type ()
           << endl;
      return 0;
    }
}
