#ifndef CONNECTFOURUNDO_H
#define CONNECTFOURUNDO_H

#include "ConnectFourPlus.h"   // ConnectFourPlus classdan inherit edebilmek icin oncelikle onun header file ni cagirdim

class ConnectFourUndo :protected ConnectFourPlus {   //ConnectFourUndo plus a benzer sekilde oynayacagindan plustan inherit ettim

public:
	ConnectFourUndo();      //default constructorunu tanimladim
	int playGame();        //mainde ConnectFourPLus un playGame ine erisimini direkt saglamasi icin bu fonksiyonumu declare ettim
	
protected:
	int oldBoard(string);  //LOAD ve SAVE komutlarini gerceklestirecek olan fonksiyonumu declare ettim
	int removeLastMove();   //Bir hamle geri almasi icin fonksiyonumu declare ettim


	
};


#endif // !CONNECTFOURUNDO_H
