#ifndef GTUSETBASE_H
#define GTUSETBASE_H
#include<string>

namespace SET{
template <class T>
class GTUSetBase{

public:
  GTUSetBase();


   virtual int erase(T) = 0;  //istenen fonksiyonlari virtuaş sekilde declare ettim
   virtual int empty() = 0; 
   virtual int clear() = 0;
   virtual int count(T) = 0;
   virtual int insert(T) = 0;
   virtual T* find(T) = 0;
   virtual GTUSetBase<T>* begin() = 0;
   virtual GTUSetBase<T>* end() = 0;
   virtual int getSize()const = 0;
   virtual  T getResult(int )const = 0 ;
   void setSize(int newSize) { size=newSize; }
   void setContent(T newContent) {content =newContent ;}

   int elementCount;  //kac tane eleman oldugunu tutacak integer
   int size;
   T content;   //data ile oynarken bu type daki contenti kullanacagim

};
}

#endif
