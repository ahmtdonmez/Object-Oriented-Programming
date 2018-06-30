#include<iostream>
#include<memory>
#include<string>
#include "GTUSet.h"

using namespace std;

using SET::GTUSet;  //namespace imi basta implement ettim ki sureki yazmak zorunda kalmayayim
using SET::GTUSetBase;
template <class T>
GTUSet<T>::GTUSet(){

elementCount=0;   //ilk degerleri initialized ettim
size=0;


}

template <class T>
GTUSet<T>::~GTUSet(){
//destructor kontorllü olrak bos birakildi
}


template <class T>
int GTUSet<T>::insert(T value )   //insert fonksiyonu icin T type inda parametre alıp insert ediyorum
{
   int check=0;
  

  for(int i=0;i<size;i++)
   if(data.get()[i].getContent() ==value)
      check=1;
 
    if((elementCount +1 >size || elementCount == 0) && check !=1)
        allocateMemory();  //eger bu sart saglnirsa daha data olusmamis olacagindan olusmasi icin fonkiyonuma gönderdim
 

    if(check!=1){
        data.get()[elementCount].setContent(value);  //fonksiyondan geldikten sonra artık atama yapiyorum
        elementCount++;  //ilk contenti atadigim icin elementCountu artirdim
        setPointer();  //datanin siralanmasi icin olusturdugum fonksiyonumu cagirdim
  
}

  return 0;
}


template <class T>
int GTUSet<T>::allocateMemory(){  //datayi genisletecek fonksiyon


 shared_ptr<GTUSet<T>> temp2(new GTUSet<T>[size+1], default_delete<GTUSet<T>[]>()); //gecici samrt pointerimi atamak icin olusturdum

 if(elementCount==0)
   data=temp2;  //eger eleman yoksa datamda o zaman datayi korumama gerek kalmadan atamayi yapiyorum


  for(int i =0; i < size; i++) 
   temp2.get()[i].setContent(data.get()[i].getContent());  //temp2 nin eski datayi tutmasi icin bir bir contentini ayarliyorum

 
shared_ptr<GTUSet<T>> temp3(new GTUSet<T>[size+1], default_delete<GTUSet<T>[]>()); // yeni temp3 u aliyorum ve size+1 olarak aliyorum

                                                          //amacım datayi genisletmek
data =temp3;   //eski datayi temp3 ile degistiriyorum

for(int i =0; i < size; i++)
   data.get()[i].setContent(temp2.get()[i].getContent());  //daha sonra temp2 de tutugum eski datayi yeni dataya atiyorum


 size++;  //size 1 arttıgindan bende tuttugum size i arttiriyorum

return 0;
}

template <class T>
void GTUSet<T>::setPointer() {  //set icindeki  valueleri duzeleyecek olan fonksiyon

   T smaller;
   int x=0;

   while (1) {
     x = 0;

     for (int i = 0; i <= size; i++) {

     if (i + 1 < size)
	if (data.get()[i].getContent() > data.get()[i + 1].getContent()) {  //kucuk olani basa secmek icin sart koyuyorum

	     smaller = data.get()[i + 1].getContent();  //kucuk olani tutuyorum
	     data.get()[i + 1].setContent(data.get()[i].getContent()); //buyuk olanla kucuk olanin yerlerini degistiryorum
	     data.get()[i].setContent(smaller); //buyugun tutugu eski yere kucugu koyuyorum
	     x = 1;

	}

  	}
		
        if (x == 0)  //eger sart saglanmıssa sonsuz loopa girmemesi icin break ettim
	   break;
	
    }
		
	
}


template <class T>
int GTUSet<T>::erase(T value){  //istenenen type daki value yi alip silecek fonksiyon

    int counter;
    int check = 0;
    int x = 0;

    shared_ptr<GTUSet<T>> temp(new GTUSet<T>[size - 1], default_delete<GTUSet<T>[]>()); //datadan silinme olacagi icin size-1 lik yeni templer
    shared_ptr<GTUSet<T>> temp2(new GTUSet<T>[size - 1], default_delete<GTUSet<T>[]>()); //olusturdum

    temp = data;  //datayi tutmasi icin temp ile esitliyorum

    for ( counter=0 ; counter < size; counter++) {
	if (data.get()[counter].getContent() == value)   //ilgili value nin oldugu yeri buluyorum
	   break;

	else
	   check++;

    }
  
 

    for (int i = 0; i < size; i++) {  //counter o valuenin yerini tuttugundan ona gelene kadar tempi normal set ederken
	if (i != counter) {
	   temp.get()[i].setContent(data.get()[x].getContent());
	   x++;
	}

	else if (i == counter) {              //eger valuenin tutuldugu deger gelirse eski datanin 1 ilerisi contentini temp e atiyorum
	    x++;
	    temp.get()[i].setContent(data.get()[x].getContent());
	    x++;  // x i 2 arttirmis oldum 1 artsaydı yukardaki sarta girdiginde valuenin yanındaki  degeri iki defa yazardi 
	}        //bunun onune gecmek icin iki defa artitridim

     }



    temp2 = temp;  //yeni temp yi temp2 e
    data = temp2;   //temp2 yi de yeni data olarak set ettim
    size--;  //size 1 azaldigindan bende bir azalttim



   return 0;

}


template <class T>
int GTUSet<T>::empty() {

   if (size == 0)  //size a bagli 0 ya da 1 donderdim sonucta bos olup olmadigi size a bagli
      return 0;

   else
      return 1;


}


template <class T>
int GTUSet<T>::clear() {

   shared_ptr<GTUSet> newData(new GTUSet[1], default_delete<GTUSet[]>()); //  direkt yeni smart pointer olusturup dataya atadim
   data = newData;
   size = 0; 
   elementCount = 0;  //tuttugum degerleri 0 ladim

  return 0;

}

template<class T>
GTUSetBase<T>* GTUSet<T>::begin() {

    GTUSetBase<T>* beginAddress;   //hocam adresi dogru return ettirdim ama ne yaptim ne ettim bir turlu iterator u dogru duzgun 
    beginAddress=data.get();  //tanimlayamadim inner class yaptim erisilemiyor hatasi verdi inherit yaptim(GTUIterator u ) yine hata verdi
                   //4 gun gec gonderme sebebim bu belirtmek istedim

  return beginAddress;

}


template<class T>
GTUSetBase<T>* GTUSet<T>::end() {

	
     GTUSetBase<T>* endAddress;  
       
     endAddress=data.get()+size;  //data.get begin adresi size eklersem de end adresini elde etmis olurum ve buna return ettim bu yuzden

  
  return endAddress;

}


template <class T>
T* GTUSet<T>::find(T value) {  // T type indaki value yi alip datada arayacak fonksiyon
	int check = 0;
	T* adress;  // adresi tutmasi icin pointer tanimladim

	for (int i = 0; i < size; i++) {
		if (data.get()[i].getContent() == value) {  //contentleri value ile kiyasladim eslesirse onun adresine return ettim
			adress = &value;
			return adress;
			
		}


		
		else
			check++;
	}

	if (check == size) {  //eslesme olmazsa diye mesaj yazdirdim
		cout << "no match" << endl;
		return 0;
	}

}




template <class T>
int GTUSet<T>::count(T value) { //ilgili value varsa data da 1 donderecek yoksa 0 donderecek olan fonksiyonum
	
   int check = 0;

   for (int i = 0; i < size; i++) {
	if (data.get()[i].getContent() == value)  //data size a ulsana kadar contentini kontrol ederek ona gore return degerimi belirledim
	    return 1;

	else
	    check++;
	
    }
  
    if (check == size)
	return 0;

}












