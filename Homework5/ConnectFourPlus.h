#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"    //base classdan inherit edebilmek icin oncelikle onun header file ni cagirdim

class ConnectFourPlus :protected ConnectFourAbstract {   //ConnectFourPLus u base classdan(ConnectFourAbstract) dan inherit ettim

public:
	ConnectFourPlus();  //default contructorunu tanimladim
	int playGame();    //mainde ConnectFourAbstract in playGame fonksiyonuna erisemeyecgimden ona erismesi icin 
                              //bu fonksiyonu declare ettim

protected:
	int checkGame();     //oyun boardunu kontrol etmesi icin gerekli olacak olan fonksiyonumu tanimladim
	int oldBoard(string);   //LOAD ve SAVE komutlarini gerceklestirecek olan fonksiyonimi tanimladim

};


#endif // CONNECTFOURPLUS_H
