#ifndef  CONNECTFOURABSTRACT_H
#define  CONNECTFOURABSTRACT_H
#include<string>
#include <vector>
#include "Cell.h"     //Cell classini kullanabilmek icin headerini cagirdim
using namespace std;

class ConnectFourAbstract {

public:
	ConnectFourAbstract();  //default constructor
	ConnectFourAbstract(int, int, char);   //overload constructor
	
protected:
	void setBoard();       //constructor ve playGame tarafından cagrilip boardu ayarlayacak fonksiyon
        int play(string);   //oyuncunun hamlesinin dogrulugunu kontrol edip  board'un içine atayan fonksiyon
	int play();         //bilgisayarin hamle yapmasini saglayacak olan fonksiyon   
	int drawBoard();            //ekrana boardu cizdirecek olan fonksiyon
	int playGame();		 //oyunu oynatacak fonksiyon
	virtual int checkGame() = 0;            // olusturdugum board'u kontrol edip oyunun bitip bitmediðinine karar verecek olan fonksiyon
	virtual int oldBoard(string) = 0; //LOAD ve SAVE komutları geldiginde calisacak fonksiyon
	int setCounter(int);
	int getCounter()const { return counter; }


	Cell** gameBoard;        //oyun boardunu olusturdum(Cell den)
	Cell temp;           //Cell den temp objesini olusturdum ki daha sonradan setters ve getters larini kullanabileyim
	int** moveOrder;

	int counter; // hamle sirasini tutmasi icin tanimladim

};


#endif // ! CONNECTFOURABSTRACT_H

