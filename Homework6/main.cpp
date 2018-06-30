#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include "GTUSetBase.h"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUSetBase.cpp"
#include "GTUMap.h"
#include "GTUMap.cpp"

using namespace std;

using MAP::GTUMap; //namespacelerimi tanimladim
using SET::GTUSet;
using SET::GTUSetBase;


template <class T>  //global functionu implement etmeden once declare ettim
std::shared_ptr<GTUSetBase<T>> setIntersection( const GTUSetBase<T>&, const GTUSetBase<T>&);


int main(){


  GTUMap<int, char> deneme;
  pair<int, char> newData;
  
  GTUMap<float, int> deneme2;
  pair<float, int> newData2;

  newData.first = 5;
  newData.second = 'f';
  
  deneme.insert(newData);

 
  newData.first = 28;
  newData.second = 'a';
  
  deneme.insert(newData);

  newData.first = 94;
  newData.second = 'z';
  
  deneme.insert(newData);
  
  newData.first = 17;
  newData.second = 'd';

  deneme.insert(newData);



   newData2.first = 6.97;
   newData2.second = 95;
   deneme2.insert(newData2);

   newData2.first = 12.68;
   newData2.second = 44;
   deneme2.insert(newData2);

   newData2.first = 47.9;
   newData2.second = 247;
   deneme2.insert(newData2);

   newData2.first = 1.6;
   newData2.second = 123;
   deneme2.insert(newData2);

   newData2.first = 5.57;
   newData2.second = 37;
   deneme2.insert(newData2);

  cout<<"\n_________________________________________________________________\n";
  cout<<"\n \t\t\t\t\t\t AHMED DONMEZ \n\t\t\t\t\t\t\t 141024008\n\n";
  cout<<"\n ------------------ Testing for int to char map --------------------\n\n";
  
     cout<<"deneme [ 17 , "<<deneme[17]<<" ] "<<endl;
     cout<<"deneme [ 94 , "<<deneme[94]<<" ] "<<endl;
     cout<<"deneme [ 28 , "<<deneme[28]<<" ] "<<endl;
     cout<<"deneme [ 5  , "<<deneme[5]<<" ] "<<endl;



     cout<<"\n ------------------ Testing for int to int map --------------------\n\n";
  
   
 
     cout<<"deneme2 [1.6, "<<deneme2[1.6]<<" ] "<<endl;
     cout<<"deneme [ 12.68 , "<<deneme2[12.68]<<" ] "<<endl;
     cout<<"deneme [ 5.57 , "<<deneme2[5.57]<<" ] "<<endl;
     cout<<"deneme [ 6.97 , "<<deneme2[6.97]<<" ] "<<endl;
     cout<<"deneme [ 12.68  , "<<deneme2[12.68]<<" ] "<<endl;


    cout<<"\n ------------------ Testing for int set deneme 3 --------------------\n\n";

     GTUSet<int> deneme3;
     for(int i=0;i<=8;i++)
       deneme3.insert(i*2+1);

     deneme3.insert(68);
     deneme3.insert(21);

 
     for(int i=0;i<deneme3.getSize();i++)
     cout<< deneme3.getResult(i)<<"    ";
    
   
     cout<<"\n\n---------- after testing set and also map erase function deneme3  --------\n\n";
    deneme3.erase(5);
    deneme3.erase(68);
    deneme3.erase(9);
 
     cout<<endl<<endl;
    for(int i=0;i<deneme3.getSize();i++)
     cout<< deneme3.getResult(i)<<"    ";

     cout<<"\n\n------- Testing count for int to char map (deneme yukarda tanimli) ---------\n\n";
  
     
    cout<<"for the key 11 count is =  "<< deneme3.count(11)<<"    "<<endl;
    cout<<"for the key 68 count is =  "<< deneme3.count(68)<<"    "<<endl;
    cout<<"for the key 21 count is =  "<< deneme3.count(21)<<"    "<<endl;
    cout<<"for the key 9 count is =  "<< deneme3.count(9)<<"    "<<endl;
    cout<<"for the key 5 count is =  "<< deneme3.count(5)<<"    "<<endl;

     cout<<"\n\n testing empty or not before clear function  (1 is not empty 0 is empty ) =  "<<deneme3.empty()<<endl;
  
    cout<<"\n\n\n";

    deneme3.clear();  //ekrana bisey basmayacagı icin sadece hata verdiirecek onun icin yazdiramadim
 
    cout<<" testing empty or not after clear function  (1 is not empty 0 is empty ) =  "<<deneme3.empty()<<endl;
  
    cout<<"\n\n\n";

   cout<<"\nAnd finally computing two set and return setIntersection \n\n";
   GTUSet<int> deneme4;
   
     for(int i=0;i<8;i++)
     deneme3.insert(i*2+5);

   for(int i=0;i<12;i++)
      deneme4.insert(i*3+4);

    cout<<"\n deneme3 =   ";
   for(int i=0;i<deneme3.getSize();i++)
      cout<<deneme3.getResult(i)<<"   ";    
  
      cout<<"\n\n";
    
    cout<<"\n deneme4 =   ";
   for(int i=0;i<deneme4.getSize();i++)
      cout<<deneme4.getResult(i)<<"   "; 

   
   cout<<"\n\n\n\n  The setINtersection result is  =     ";



   shared_ptr<GTUSetBase<int>> resultSet(new GTUSet<int>);

  resultSet =setIntersection(deneme3,deneme4);

   for(int i=0; i<resultSet->getSize(); i++  )
     cout<<resultSet->getResult(i)<<"    ";
  

 cout<<"\n\n\n ____________________ END OF THE MAİN ___________________\n\n\n";
 
  return 0;
}

using SET::GTUSetBase;


template <class T>  //global functionu implement etmeden once declare ettim
std::shared_ptr<GTUSetBase<T>> setIntersection( const GTUSetBase<T>& set1, const GTUSetBase<T>& set2)
{

   shared_ptr<GTUSetBase<T>> intersectionSet(new GTUSet<T>);

   for(int i = 0; i < set1.getSize(); i++)
      for(int j = 0; j < set2.getSize(); j++)
         if(set1.getResult(i) == set2.getResult(j))
             intersectionSet->insert(set1.getResult(i));

   
    return intersectionSet;


}



