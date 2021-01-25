#include "Sort_Observer.h"

template <class T>
class Acceptor_Observer : public Sort_Observer
{
public:
  Acceptor_Observer() 
  {
  }
  
  virtual ~Acceptor_Observer();
  
  void update_sort (const Sort_Info_Base &sort_observation) {
    if (sort_observation.status() == Sort_Info_Base::SORTED) {
	  Holder = (dynamic_cast<Sort_Info<T>&>(const_cast<Sort_Info_Base&>
	  (sort_observation))).data();
    }
  }

  void get_data(Array<T>& holder) {
    holder = Holder;
  }

private:
  Array<T> Holder;

};

template <class T>
Acceptor_Observer<T>::~Acceptor_Observer(){}
