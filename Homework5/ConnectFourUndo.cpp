#include<iostream>
#include <string>

#include "ConnectFourPlus.h"   //ConnectFourPlus classini kullanabilmek icin headerini cagirdim
#include "ConnectFourUndo.h"     //ConnectFourUndo Classinin declarationu burda olacagindan headerini cagiriyorum


ConnectFourUndo::ConnectFourUndo(){

//declarationu gerekli olmadigindan yapilmadi

}  

int ConnectFourUndo::playGame() {

	ConnectFourPlus::playGame();    //mainden cagrilacak olan playGame i ConnectFourPLus ın playGame ini calistirmak icin kullandim
	return 0;
}

int ConnectFourUndo::oldBoard(string input) {
	
	if (input != "UNDO")  //oldBoard daima input string oldugunda cagrilacak bende girilen inputun kontrolunu yapiyorum
	   ConnectFourPlus::oldBoard(input); //UNDO degilse burada yapilacak bisey yok geri ConnectFourPLus in oldBoardununa yonlendiriyorum

	else if (input == "UNDO")   //UNDO gelmisse son hamle geriye almak icin declare ettigim fonksiyonumu cagirdim
		removeLastMove();

	return 0;

}

int ConnectFourUndo::removeLastMove() {  //son hamleyi bulup geri alacak olan fonksiyon

	string move;
	int row = temp.getRow();
	int column = temp.getColumn();
	int rowToRemove = 0;     //row ve column degeriyle oynamamak icin son hamlenin row unu tutacak integer tanimladim
	int columnToRemove = 0;   //row ve column degeriyle oynamamak icin son hamlenin columun unu tutacak integer tanimladim
	char mode = temp.getMode();  // oyunun modunu aliyorum ki son hamle geri alindiginda kimden input alacagimi bileyim

	int check = 0;   // check i moveOrder(hamleSirasini) la karsilastirarak son hamleyi bulmak icin tanimladim

	for (int i = row-1; i >=0; i--) 
		for (int j = 0; j < column; j++) {
		
			if (moveOrder[i][j] > check) {   //ic ice for loop kullanarak en moverOrder contentinin en buyuk oldugu yeri aldim
				check = moveOrder[i][j];  //moveOrder hamle sirasini 1,2,3... seklinde tutan iki boyutlu array 
				rowToRemove = i;
				columnToRemove = j;
			
			}

			


		}




	moveOrder[rowToRemove][columnToRemove] = 0;  // artik en son hamleyi buldugundan moveOrder daki yerini sifirliyorum

	
	gameBoard[rowToRemove][columnToRemove].setChoose('_');  //ilgili yerdeki hamleyi geri aliyorum


	cout << endl << endl; 


	
	if (temp.getPlayerTurn() == "player2" && mode =='P') {  //oyun PVP oynaniyorsa son hamleyi alan kisinin hamle yapmasini sagliyorum

	    ConnectFourPlus::drawBoard();
	    temp.setPlayerTurn("player2");  //player2 undo demis olacagindan siradaki hamleyi onun yapabilmesi icin playerTurnu ayarliyorum
	    cout << "\n Your last move has been removed, player2 enter a move = ";
	 	cin >> move;

	}

	else if (temp.getPlayerTurn() == "player1" && mode == 'P') {//oyun PVP oynaniyorsa son hamleyi alan kisinin hamle yapmasini sagliyorum

	    ConnectFourPlus::drawBoard();  
	    temp.setPlayerTurn("player1"); //player1 undo demis olacagindan siradaki hamleyi onun yapabilmesi icin playerTurnu ayarliyorum
	    cout << "\n your last move has been removed, player1 enter a move = ";
	    cin >> move;

	}
	
	else if (mode == 'C') {  //bilgisayara karsi oynaniyorsa oyun bilgisyarin hamleyi geri almasi lazim(her turlu en son o yapacagindan)

		temp.setPlayerTurn("player2"); //O koymasi icin player2 diye ayarliyorum
		cout << " \nThe last move of compueter has been removed \n\n \t\t the computer put its new move ";

		ConnectFourPlus::play(); //direkt playGame cagrilirsa player hamle yapar onun icin once bilgisayarin hamlesini aliyorum
		ConnectFourPlus::drawBoard(); //ekrana boardu basiyorum

		temp.setPlayerTurn("player1");  //artik bilgiyar hamle yaptigi icin playerTurnu set ediyorum
		cout << "\n Now your turn, enter your move = ";
		ConnectFourPlus::playGame();  //oyunun oynanmaya devam etmesi icin fonksiyonumu cagiriyorum

	//inherit class oldugu icin plus(plus da abstractan aliyor yani gerekli fonksiyonlari rahatlikla declare edebiliyorum
	}
	

	ConnectFourPlus::play(move); //oyun PVC olmadiginda yukardaki set ettigim sekilde hamle yapmasi icin fonksiyonumu cagiriyorum
	ConnectFourPlus::playGame();   //oyun PVC ise buralara gelmeden playGame e gitmis olacak zaten

	return 0; //fonksiyonumu sonlandiriyorum

}


