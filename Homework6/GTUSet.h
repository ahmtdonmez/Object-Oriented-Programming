#ifndef GTUSET_H
#define GTUSET_H
#include <iostream>
#include <memory>
#include <string>

#include "GTUSetBase.h"


using namespace std;

namespace SET{
template <class T>
class GTUSet: public GTUSetBase<T>{

public:

   GTUSet();
   ~GTUSet();
   T getContent()const { return content; }
   int getSize()const {return size;}
   T getResult(int i)const{ return data.get()[i].getContent(); }
   int allocateMemory();
   int insert(T);
   int erase(T);
   int empty();
   T* find(T);
   GTUSetBase<T>* begin();
   GTUSetBase<T>* end();
   int count(T);
   void setPointer();
   int clear();






   shared_ptr<GTUSet> data;
   using GTUSetBase<T>::size;  //baska türlü base classın degerini kullanamıyorum hata veriyor hocam 
   using GTUSetBase<T>::content;  //o yüzden onu kullandıgımı belirtiyorum
   using GTUSetBase<T>::elementCount;

};
}

#endif
