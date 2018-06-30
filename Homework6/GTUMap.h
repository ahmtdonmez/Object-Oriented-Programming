#ifndef GTUMAP_H
#define GTUMAP_H
#include <utility>
#include "GTUSet.h"
#include <string>
using namespace std;
using SET::GTUSet;

namespace MAP{
template <class K, class V>
class GTUMap: public GTUSet<std::pair<K,V>> {

public:
  GTUMap(): key(0), value(0){}
  ~GTUMap();

  V& operator[](const K&);

private:
  K key;
  V value;
   using GTUSet<std::pair<K,V>>:: size;
   using GTUSet<std::pair<K,V>>:: content;  //public yapmama ragmen degerlere erisilemşyor dediginden bunu kullandim
   using GTUSet<std::pair<K,V>>:: data;

};




}

#endif
