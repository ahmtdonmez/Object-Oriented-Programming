#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

class ConnectFourDiag :protected ConnectFourAbstract {  //ConnectFourDiag i base class dan inherit ettim 

public:
	ConnectFourDiag();   //Default constructorunu tanimladim
	int playGame();      //base classin playGame i protected oldugundan mainde cagirabilmek icin kendi fonksiyonunu olusturdum

private:
	int checkGame();     //oyun sadece capraz biteceginden daha onceden base de virtual yaptigim fonksiyonu tanimladım
	int oldBoard(string);   //eski oyunu yukleyecek fonksiyonumu tanimladim


};



#endif // CONNECTFOURDIAG_H
