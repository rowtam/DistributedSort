#ifndef DISTRIBUTED_SORT_C
#define DISTRIBUTED_SORT_C

#include "Distributed_Sort.h"
#include "String.h"
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>  /* for close () and sleep () */
#include "Timer.h" /* for gethrtime(void) */


/*
Distributed_Sort constructor reads IP addresses from
distributed_sort.cfg. and splits up the array bases on
the number of IPs
*/

template <class T>
Distributed_Sort<T>::Distributed_Sort(const Sort_Info<T> &s)
  :array_data_(s.data())
{
  progress_ = Distributed_Sort::NOT_STARTED;
  ifstream ifstr("Distributed_Sort.cfg");
  char buf[20];
  numIPs = 0;
  while (!ifstr.eof()) {
    ifstr.getline(buf, 255);
    ++numIPs;
  }
  --numIPs;
  ifstream ifstr2("Distributed_Sort.cfg");
  Array<String> IParray(numIPs);
  cout << "\nReading IP address from Distributed_Sort.cfg\n" << endl;
  for (int num = 0; num < numIPs; num++) {
    ifstr2.getline(buf, 255);
    IParray[num] = String(buf);
    cout << IParray[num] << endl;
  }
  int concount = 0;  // keep count of number of connectors.
  int i = 0; 
  partition_size = array_data_.size()/numIPs;
  cout <<"\nNumber of machines in use: "<< numIPs <<endl;
  connectors = Array<Connector<T>*>(numIPs);
  cout << "Partition Size : " << partition_size << endl;
  while(i < array_data_.size()) {
    int linesofdata = partition_size;
    if (concount == numIPs - 1)
      linesofdata = array_data_.size() - i;
    cout << "Partition of size : " << linesofdata << endl;
    Array<T> temp(linesofdata); 
    int k = 0;
    for (int j = i; j - i < temp.size(); j++) {
      temp[k] = array_data_[j];
      ++k;
    }
    i = j; 
    Sort_Info<T> srt(Sort_Info_Base::QUICK_SORT, temp,
Sort_Info_Base::UNSORTED);
    cout << "Connector to " << IParray[concount] << " created. " <<
concount << endl;
    connectors[concount] = new Connector<T>(srt,
IParray[concount].getbuf(), 6020);
    ++concount;
  }
}

/*
Destructor
*/
template <class T>
Distributed_Sort<T>::~Distributed_Sort()
{
  for(int i = 0; i < connectors.size(); ++i)
    delete connectors[i];
}

template <class T>
int Distributed_Sort<T>::start_sort()
{
  if (progress_ != Distributed_Sort::NOT_STARTED) {
    cout << "Sort is either in progress or finished." << endl;
    return -1;
  }
  progress_ = Distributed_Sort::STARTED;
  cout << "Distributed Sort Start" << endl;
  Timer t;
  t.start_time();
  Array< Array<T> > sorted(numIPs);
  for(int i = 0; i < connectors.size(); i++) {
    connectors[i]->send_to_server();
  }
  for(i = 0; i < connectors.size(); i++) {
    connectors[i]->get_data(sorted[i]);
  }
  Array<Sort_Info<T>*> sortinf(numIPs);
  for (i = 0; i < connectors.size(); i++) {
    sortinf[i] = new Sort_Info<T>(Sort_Info_Base::QUICK_SORT, sorted[i],
	Sort_Info_Base::SORTED);
  }
  Merge_Sort<T> ms(sortinf);
  Distributed_Sort_Observer<T> dso(*this);
  ms.register_observer(dso);
  ms.start_sort();
  t.stop_time();
  cout << "Distributed Sort Stop" << endl;
  cout << "Distributed Sort Time" << endl;
  t.display_time();
  progress_ = Distributed_Sort::FINISHED;
  Sort_Info<T> srt2(Sort_Info_Base::QUICK_SORT, Observation, 
Sort_Info_Base::SORTED);
  publish_sort_update(srt2);
  for (int f = 0; f < numIPs; f++) {
    delete sortinf[f];
  }
  cout << "Here's the time again:" << endl;
  t.display_time();
  return 0;
}

template <class T>
void Distributed_Sort<T>::set_Observation(Array<T>& arrays)
{
  this->Observation = arrays;
}

#endif
