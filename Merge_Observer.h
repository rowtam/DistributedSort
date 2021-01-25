#include "Sort_Observer.h"
#include "Merge_Sort.h"

template <class T>
class Merge_Observer : public Sort_Observer
{
public:
  Merge_Observer(Merge_Sort<T>& smerge) 
    :supermerge(smerge)
  {
  }
  virtual ~Merge_Observer();
  void update_sort (const Sort_Info_Base &sort_observation) {
    if (sort_observation.status() == Sort_Info_Base::SORTED) {
	  //supermerge.set_Observation((dynamic_cast<Sort_Info<T>&>(sort_observation)).data());
	  supermerge.set_Observation((dynamic_cast<Sort_Info<T>&>(const_cast<Sort_Info_Base&>(sort_observation))).data());
    }
  }

private:
  Merge_Sort<T>& supermerge;

};

template <class T>
Merge_Observer<T>::~Merge_Observer(){}
