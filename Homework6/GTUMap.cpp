#include <iostream>
#include <string>
#include "GTUMap.h"

using SET::GTUSet;
using MAP::GTUMap;  //namespacelerimi tanimladim

template <class K, class V>
GTUMap<K,V>::~GTUMap() {}


template <class K, class V>
V& GTUMap<K,V>::operator[](const K& k) {

  V* adress;
  int check=0;
  
  for(int i=0; i< size; i++){
   if((data.get()[i].getContent()).first == k){

       value=(data.get()[i].getContent()).second;  //operatoru istenen sekilde overload ettim key ile gelen inputu karsilastirdim
       adress=&value;   //esit olursa adress ile tttugum pointera atadim(V type inda) ve onun gosterdigi degere return ettim
       
       return *adress;

}
    else 
    check++;
   

}
  try{
   
     if(check<size)  //eger silinmis veya olmayan content varsa boyle bir hata veridirdim
      cout<<"no error"<<endl;
 
     else
       throw 10;
   
  } catch(int error){
  
     cout<<"bu key icin kayitli value bulunamadi error >>  "<<error<<endl<<endl;
   
}

 
}

