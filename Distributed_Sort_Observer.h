#include "Sort_Observer.h"
#include "Distributed_Sort.h"

template <class T>
class Distributed_Sort_Observer : public Sort_Observer
{
public:
  Distributed_Sort_Observer(Distributed_Sort<T>& DS) 
    :ds_(DS)
  {
  }
  virtual ~Distributed_Sort_Observer();
  void update_sort (const Sort_Info_Base &sort_observation) {
    if (sort_observation.status() == Sort_Info_Base::SORTED) {
        ds_.set_Observation((dynamic_cast<Sort_Info<T>&>
                            (const_cast<Sort_Info_Base&>
                            (sort_observation))).data());
    }
  }

private:
  Distributed_Sort<T>& ds_;

};

template <class T>
Distributed_Sort_Observer<T>::~Distributed_Sort_Observer(){}
