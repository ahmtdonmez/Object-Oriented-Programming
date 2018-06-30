#include<iostream>
#include<string>
#include <fstream>

#include "ConnectFourPlus.h"
#include "ConnectFourAbstract.h"

using namespace std;


ConnectFourPlus::ConnectFourPlus() :ConnectFourAbstract(){}

int ConnectFourPlus::checkGame() {

   int row = temp.getRow();
   int column = temp.getColumn();

   int check[4] = { 0 };
   int a = 1;
   int gameOver = 0;
		
//dikey  ve yanlamasÜna kontrol
   
   for (int i = (row - 1); i >= 0; i--) {

      for (int j = (column - 1); j >= 0; j--) {

	 for (int x = 0; x <= row - 1; x++) {   //computerMove da oldugu gibi en alt satÜr ve stundan yukari dogru kontrol ediyoum

	    if ((gameBoard[x][j].getChoose() == 'X'))  //X gördigim yerde daha önceden tanimladigim dizinin birinci elemanini arttiriyorum
                check[0]++;

	    if (gameBoard[x][j].getChoose() != 'X')     //X görmedigi zaman 0 laniyor
		check[0] = 0;

            if (gameBoard[x][j].getChoose() == 'O')       //ayni sekilde O karakteri içinde kontrol ediyorum
		check[1]++;

	    else if (gameBoard[x][j].getChoose() != 'O')    // O karkaterini görmedigi zaman sifirlaniyor
		check[1] = 0;

	    if (check[0] == 4) {  

		for (int c = 0; c <= 3; c++)
		   gameBoard[x - c][j].setChoose('x'); 

	        gameOver = 1;    
	        break;         

	     }

	     if (check[1] == 4) {

	       for (int c = 0; c <= 3; c++)
		 gameBoard[x - c][j].setChoose('o');

	       gameOver = 2;   
	       break;

	      }



	}  // en içteki for un sonu



	if (gameOver == 1 || gameOver == 2)   
	   break;

	if (gameBoard[i][j].getChoose() == 'X')    
	   check[2]++;

        if ((check[2] <= 3 && j == 0))   
	   check[2] = 0;

	else if (gameBoard[i][j].getChoose() != 'X')   // X görmediði zaman sÜfÜrladÜm
	   check[2] = 0;

	if (gameBoard[i][j].getChoose() == 'O')     // O gordugunde olusturdugum dizinin 4. elemanÜnÜ arttÜrdÜm
	   check[3]++;

	if ((check[3] <= 3 && j == 0))      
	    check[3] = 0;                    


	else if (gameBoard[i][j].getChoose() != 'O')  //O görmezse sifirlanacak
	    check[3] = 0;

	if (check[2] == 4) {          

	   for (int b = 0; b <= 3; b++)
		gameBoard[i][j + b].setChoose('x');


	   gameOver = 3;         
	   break;   

	}

	if (check[3] == 4) {        

	  for (int b = 0; b <= 3; b++)
	     gameBoard[i][j + b].setChoose('o');

	  gameOver = 4;
	  break;              // O kazandÜðÜndan çift sayÜya return edip oyunu sonlandÜrÜyorum

	}



    }

    if (gameOver == 1 || gameOver == 2)    // yukardaki sartlar saglandÜgÜnda fonksiyondan tamamen cÜkmasÜnÜ saglÜyorum
	break;

    if (gameOver == 3 || gameOver == 4)   //sondaki döngÌnÌn tekrarlanmasÜnÜn önÌne geciyorum yani
	break;

  }  // en dÜßtaki for için son





  return gameOver;     //gameOver degiskenine dönderiyorum ki kimin yendigini daha sonra kontrol edebileyim

 }

int ConnectFourPlus::oldBoard(string input) {

   if (input == "SAVE") {

     int row = temp.getRow();   //gerekli bilgileri getterslar yardimiyla aldim ve atadim
     int column = temp.getColumn();
     char mode = temp.getMode();
     string playerTurn = temp.getPlayerTurn();

     string fileName;  //kaydedilecek olan dosyanin ismini tutacak
     string move;     //yapilacak hamleyi tutacak
     char a;
     ofstream file;   //dosyayi yazmak icin ofstream sekilnde tanimliyorum

     cout << " Enter file name to save in = ";

     cin.ignore();  //getline i etkilemesin diye koydum
     getline(cin,fileName);

     file.open(fileName.c_str(), ios::out);  //verilen isim icin dosya aciyorum

     if (file.is_open()) {     //acilirsa gerekli bilgileri sirayla yazdiriyorum

	file << row << endl << column << endl << mode << endl << playerTurn << endl ;

	for (int i = 0; i < row; i++)
	    for (int j = 0; j < column; j++)
		file << gameBoard[i][j].getChoose() << endl;  //en son boardumu yazdiriyorum

			
     }
		
     else if (!file.is_open()) {  //eger dosya acilmazsa cerr ile hata mesaji verdiriyorum
	
         cerr << "Error to opening file so you are redirecting the game where before you enter " << input << endl << endl;
         file.close();
	 playGame();

     }

     file.close();   //dosyayi kapatiyorum

     cout << "\n The board succesfully saved \n You can go back that board any time you want  \n by saying LOAD " << input << endl << endl;

     if (playerTurn == "player2") {   //player 2 de kalmissa sira playGame e gonderirsem arada hamlesi gider o yuzden hamlesini aliyorum

        drawBoard();
	cout << "\n player2 make a move = ";
	cin >> move;
	play(move);

      }


      playGame();  // oyunu donderen fonksiyonuma geri donuyorum
	
   }


  if (input == "LOAD") {   //LOAD gelirse tekrar oyunu yuklemek icin islemleri yaptiriyorum

     int row, column;
     char mode;
     string playerTurn;
     string fileName;    //atama yapacagim degerleri bir bir declare ediyorum
     char a;
     string move;
			
     ifstream lastGame;    //dosyadan okumak icin gerekli sartlari olusturuyorum

     cout << " \n Enter file name to load board = ";
     cin.ignore();    //daha onceden input gelirse engelliyorum
     getline(cin,fileName);

			

     lastGame.open(fileName.c_str(), ios::in);      //gelen isime gore dosyayı aciyorum

     if (lastGame.is_open()) {     //dosya acilirsa yazdirdigim sekilde sirasiyla okuyup degerleri atiyorum

	lastGame >> row >> column >> mode >> playerTurn;

	temp.setRow(row);         // okudugum degerleri bir bir set ediyorum
	temp.setColumn(column);     
	temp.setMode(mode);
	temp.setPlayerTurn(playerTurn);


	for (int i = 0; i < row; i++)
	    for (int j = 0; j < column; j++) {
		lastGame >> a;     //boardu set etmek icin ilk once a ya atiyorum daha sonra choose u a yaridimiyla set ediyorum
		gameBoard[i][j].setChoose(a);

	    }

	}

	else if (!lastGame.is_open()){        //eger dosya acilmazsa cerr ile hata verdiriyorum
	   cerr << " Sorry we are in trouble to load the board \n make sure that you entered right fileName \n or check the filename path ";

	 
            }

          lastGame.close();     //dosyayi kapatiyorum

           cout << " \n Your last size information ==>> row = " << row << " , column = " << column << endl; //guncel bilgileri ekrana basiyorum

	   if (mode == 'C') {

	       cout << "\n And you were playing with computer " << endl;
	       cout << " Here is the board lets play :) " << endl << endl;


	    }

	    if (mode == 'P' && playerTurn == "player2") { 

		drawBoard();   //PVP oyun oynaniyorsa ve oyun sirasi player2 de kalmissa ilk once onun hamlesini aliyorum 
		cout << "\nThe game mode was PVP and the we were taking move from player2 \n\t\t so player2 enter your move = ";
		cin >> move;
		play(move);

	     }

  //else koymadim cunku yukardaki sart saglanmadigi surece normal sirada oynanir oyun
	  playGame();

   }

  return 0;
	
 }

int ConnectFourPlus::playGame() {

   ConnectFourAbstract::playGame();  //mainden base classin playGame ine erisemeyecegimden dolayi kendi playGame inden base inkini cagiriyorum 

   return 0;

}





