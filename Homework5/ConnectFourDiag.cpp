
#include <iostream>
#include <string>
#include <fstream>
#include "ConnectFourDiag.h"
#include "ConnectFourAbstract.h"


ConnectFourDiag::ConnectFourDiag() :ConnectFourAbstract() {

//herhangi bir atama yapilmasina gerek olmadigindan kontrollu olarak bos biraktim

}


int ConnectFourDiag::playGame() { 

    ConnectFourAbstract::playGame();  //mainde ConnectFourAbstract in playGame fonksiyonuna erisilemyeceginden kendi playGame fonksiyonunu
                                         //olusturdum ve base classinkini cagirdim dolayisiyla mainde de bunu cagiriyorum

    return 0;

}

int ConnectFourDiag::oldBoard(string input) {

   if (input == "SAVE") {
      
     int row = temp.getRow();   //gerekli bilgileri getterslar yardimiyla aldim ve atadim
     int column = temp.getColumn();
     char mode = temp.getMode();
     string playerTurn = temp.getPlayerTurn();

     string fileName;   //kaydedilecek olan dosyanin ismini tutacak
     string move;  //yapilacak hamleyi tutacak
  
     ofstream file;   //dosyayi yazmak icin ofstream sekilnde tanimliyorum

     cout << " Enter file name to save in = ";
     cin.ignore();  //getline i etkilemesin diye koydum
     getline(cin,fileName);

     file.open(fileName.c_str(), ios::out);  //verilen isim icin dosya aciyorum

     if (file.is_open()) {  //acilirsa gerekli bilgileri sirayla yazdiriyorum
 
	file << row << endl << column << endl << mode << endl << playerTurn << endl ;

	for (int i = 0; i < row; i++)
	    for (int j = 0; j < column; j++)   //en son boardumu yazdiriyorum
		file << gameBoard[i][j].getChoose() << endl;

			
     }
		
     else if (!file.is_open()) {  //eger dosya acilmazsa cerr ile hata mesaji verdiriyorum
	
         cerr << "Error to opening file so you are redirecting the game where before you enter " << fileName << endl << endl;
         file.close();
	 playGame();  //dosyayi kapatip oyunu kaldigi yerden devam etmesi icin playGame fonksiyonumu cagriyorum

     }

     file.close();  //dosya acilmisssa yukaridaki sart saglanmayacagindan dosya orada kapanmayacak ben de burda kapatiyorum

     cout << "\n The board succesfully saved \n You can go back that board any time you want  \n by saying LOAD " << input << endl << endl;

    //oyun kaydedilirse kaydedilgini ekrana basiyorum daha sonra hangi player da kalmissa en son ona gore devam ettiriyorum

     if (playerTurn == "player2") {  //player 2 de kalmissa sira playGame e gonderirsem arada hamlesi gider o yuzden hamlesini aliyorum

        drawBoard();                  
	cout << "\n player2 make a move = ";
	cin >> move;
	play(move);

      }

  //player1 icin sart koymadim cunku playGame zaten player1 in hamlesini alarak basliyor

      playGame();
	
   }


  if (input == "LOAD") {   //LOAD gelirse tekrar oyunu yuklemek icin islemleri yaptiriyorum

     int row, column;
     char mode;
     string playerTurn;   //atama yapacagim degerleri bir bir declare ediyorum
     string fileName;
     char a;
     string move;
			
     ifstream lastGame;   //dosyadan okumak icin gerekli sartlari olusturuyorum

     cout << " \n Enter file name to load board = ";   //okunacak dosyanin adini istiyorum
     cin.ignore();   //daha onceden input gelirse engelliyorum
     getline(cin,fileName);

			

     lastGame.open(fileName.c_str(), ios::in);  //gelen isime gore dosyayı aciyorum

     if (lastGame.is_open()) {  //dosya acilirsa yazdirdigim sekilde sirasiyla okuyup degerleri atiyorum

	lastGame >> row >> column >> mode >> playerTurn;

	temp.setRow(row);    // okudugum degerleri bir bir set ediyorum
	temp.setColumn(column);
	temp.setMode(mode);
	temp.setPlayerTurn(playerTurn);


	for (int i = 0; i < row; i++)
	    for (int j = 0; j < column; j++) {
		lastGame >> a;   //boardu set etmek icin ilk once a ya atiyorum daha sonra choose u a yaridimiyla set ediyorum
		gameBoard[i][j].setChoose(a);

	    }

	}

	else if (!lastGame.is_open())  //eger dosya acilmazsa cerr ile hata verdiriyorum
	   cerr << " Sorry we are in trouble to load the board \n make sure that you entered right fileName \n or check the filename path ";
          
           

	   

          lastGame.close();   //dosyayi kapatiyorum

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




int ConnectFourDiag::checkGame() {

    int row = temp.getRow();

    int column = temp.getColumn();

    int check[8] = { 0 };
    int i = row - 1;
    int a = 1;
    int j = 0;
    int control = 0;
    int gameOver = 0;
    int gameOver1 = 0;
    int d = row - 1;

	

//sol taraftan çapraz kontrol


    while (i >= 0) {   
					 
        while (j != (row - a + 1)) {   
	 
           if (gameBoard[i][j].getChoose() == 'X')  
	       check[0]++;

	   else if (gameBoard[i][j].getChoose() != 'X')    //arka arkaya gelmiyorsa sÜfÜrladÜm
	       check[0] = 0;

	   if (i == 0 && j <column-1 && check[0] < 3) //2*2 boyutuna kadar dÌstgÌnde check hala 4 olmamÜssa daha olamyÜcagÜndan böyle yaptÜm
	       check[0] = 0;

	   if (gameBoard[i][j].getChoose() == 'O')      //O için kontrol ettim
	       check[1]++;

	   else if (gameBoard[i][j].getChoose() != 'O')      // arka arkaya gelmiyorsa sÜfÜrladÜm
	       check[1] = 0;

	   if (i == 0 && j < column -1 && check[1] < 3)
	       check[1] = 0;

	   if (check[0] == 4) {          // olurda 4 tane X çapraz gelmißse gelen yerleri kÌçÌk x yaptÜm

	       for (int b = 0; b <= 3; b++)
		    gameBoard[i + b][j - b].setChoose('x');

	       gameOver = 3;            //gameOver a tek sayÜ atadÜm
	       break;        //döngÌden cÜkardÜm

	    }

	    if (check[1] == 4) {    //eðer 4 tane O gelmißsse gelen yerleri kÌçÌk o ile deðißtirdim

		for (int b = 0; b <= 3; b++)
		     gameBoard[i + b][j - b].setChoose('o');

		gameOver = 4;
		break;

	     }

	i--;   //sol tarafta en asagÜdan baslayÜp çapraz bakmasÜ için i'yi azaltÜp j'yi arttÜrdÜm
	j++;


     }

     a++;   //a yÜ her seferinde 1 arttÜrarak satÜr sayÜsÜnÜn 0 dan kÌçÌk olmadan döngÌden cÜkmasÜnÜ sagladÜm( i< row-a  oldugundan)
     i = row - a;  //bir Ìst satÜra çÜkmasÜnÜ saðladÜm  ki tekrar çapraz arayabilsin
     j = 0;           //j yi sÜfÜrladÜm ki bir Ìst satÜra cÜktÜgÜnda en sagdan yani boyut kac ise oradan baslasÜn kontrol etmeye



 }   //sol taraftan capraz kontrol sonu



    i = row - 1;   //  degerleri eski haline dönderiyorum ki asagÜdaki loop dÌzgÌn calÜssÜn
    a = 1;
    j = row - 1;

    int b = 0;    //bir b intger'Ü tanÜmladÜm


////////// sag taraftan çapraz kontrol

     while (i >3) {   // en Ìst satÜra cÜktÜktan sonra artÜk capraz aramamak için

	while (j >= (a - 1)) {   // sonucta 4 tane capraz olabilmesi için i=5 den baslÜyorsa i=1 oldugunda j=5 olmalÜ o yÌzden bu sartÜ koydum

	    if (gameBoard[i][j].getChoose() == 'X')  //arka arkaya bu geliyor mu anlamak için yazdÜm
		check[2]++;

	    else if (gameBoard[i][j].getChoose() != 'X')     //gelmiyorsa sÜfÜrladÜm
		check[2] = 0;

	    if (gameBoard[i][j].getChoose() == 'O')    // arka arkaya O geliyormu diye kontrol ettim
		check[3]++;

	    else if (gameBoard[i][j].getChoose() != 'O')    // gelmiyorsa ddiye sÜfÜrladÜm
		check[3] = 0;

	    if (check[3]< 1 && i <= 3)   // bu sart saglandÜgÜnda kontrol etmesine gerek yok cÌnkÌ 4 tane arka arkaya olamayacak
		check[3] = 0;

	    if (check[2] == 4) {      //4 tane X ilen yeri kÌçÌk x ile deðißtiriyorum

		for (int b = 0; b <= 3; b++) {

		     gameBoard[i + b][j + b].setChoose('x');

	        }

	    gameOver = 5;   // X geldði için tek sayÜya atÜyorum
	    break;  // döngÌden cÜkmasÜnÜ saglÜyorum

	}

     if (check[3] == 4) {       // 4 tane O gelmißßse onlarÜ kÌçÌk o ile deðißtiriyorum

	for (int b = 0; b <= 3; b++) {

	   gameBoard[i + b][j + b].setChoose('o');

	}

        gameOver = 6;    //çift sayÜya atÜyorum
	break; //döngÌden cÜkartÜyorum

     }


      i--;
      j--;


     }

     if (gameOver == 5 || gameOver == 6)
         break;

     a++;
     i = row - a;     //0. satÜra geldiginde de loop'un devam etmmesi için bu degere atadÜm
     j = row - 1;     // sol çaprazdan en alt satÜrdan baslayp sÌtun sÌtun sola kayabilmesi için bu ifadeye atadÜm j'yi



  }  //sag tarfatan çapraz kontrol   sonu



//////  en altta 0 ve row-1 arasynda kalan sag caprazlarÜ degerlendirmek için

      i = row - 1;  //degerleri asagÜdaki loop için tekrar ayarladÜm
      j = 1;
      a = 1;

	while (j != row && (row - a) >= 3) {   

	    while (j <= (row - 1)) {    //bunu kullanarak boyutu aßmanÜn önÌnde gectim

		if (gameBoard[i][j].getChoose() == 'X')  //X görÌrse arttÜrmasÜn için olusturdum
		   check[4]++;

		else if (gameBoard[i][j].getChoose() != 'X')        // arka arkaya gelmezse sÜfÜrlasÜn diye olusturdum tekrar
		   check[4] = 0;

		if (gameBoard[i][j].getChoose() == 'O')       // O gelirse diye
		   check[5]++;

		else if (gameBoard[i][j].getChoose() != 'O')         //arka arkaya gelmezse diye bunu da sÜfÜrladÜm
		   check[5] = 0;


		if (check[4] == 4) {  // 4 tane gelirse oyunun bitmesini saglamak için gerekli gameOver sayÜsÜnÜ alÜyorum

		   for (int b = 0; b <= 3; b++)
		       gameBoard[i + b][j - b].setChoose('x'); // 4 olan yerleri kucuk x yapÜyorum

		       gameOver = 7; //X geldigi icin tek sayÜya atÜyorum
		       break;

		}

		if (check[5] == 4) {  // O gelmisse eðer 4 defa gelen yerleri kucuk yapÜyorum

		    for (int b = 0; b <= 3; b++)
			gameBoard[i + b][j - b].setChoose('o');

		    gameOver = 8;     //cift degere atÜyorum
		    break;           // loop tan cÜkarÜyorum

		}

	 i--;   // aradki acÜgÜ capraz kontrol edebilmesi icin i'yi azaltÜp j'yi arttÜrÜyorum
	 j++;

	}

	if (gameOver == 7 || gameOver == 8)
	   break;         //oyun bitmisse looptan cÜkartÜyorum

	i = row - 1;  // i yi yine en alt satÜr alÜyorum
	j = a + 1;   //j'yi a kadar arttÜrÜyorum ki saga birer birer kaysÜn hep
	a++;    // a'yÜ bir arttÜrÜyorum ki j istenilen degere ulassÜn ve en dÜstaki döngÌ kontrol edilsin diye


  }   // alt acÜktaki sað caprazlarÜ bulan loop'un sonu



        i = row - 1;      // degerleri asagÜdaki loop u dogru çalÜstÜrmak için tekrar degistirdim
	j = row - 2;
	a = 3;



	// en altta arada kalan sola dogru capraz kalan aynÜ hamleleri bulan kontrol loop'u


	while (j >= 2) {   //board'un dÜsÜna cÜkmamasÜ için gerekli kosullarÜmÜ loop'larÜn içerisinde tanÜmlÜyorum

		while (j >= 0 && i >= 0) {    //boyutu asmamak icin bu sartÜ yazdÜm

			if (gameBoard[i][j].getChoose() == 'X') // 4 tane X yanyana gelme kontrolu
				check[6]++;

			else if (gameBoard[i][j].getChoose() != 'X')    //gelmemisse sÜfÜra atama
				check[6] = 0;

			if (gameBoard[i][j].getChoose() == 'O')         //4 tane yanyana O gelme kontrolu
				check[7]++;

			else if (gameBoard[i][j].getChoose() != 'O')     //gelmemÜsse sÜfÜra atama
				check[7] = 0;


			if (check[6] == 4) {  //4 tane X gelmißsse gelen yerleri kÌçÌk yaptÜm ki oynayan görsÌn

				for (int b = 0; b <= 3; b++)
				     gameBoard[i + b][j + b].setChoose('x');

				gameOver = 9;
				break;

			}

			if (check[7] == 4) {  //4 tane O gelmisse onlarÜ kucuk yaptÜm ki oynayan gorsun

				for (int b = 0; b <= 3; b++)
					gameBoard[i + b][j + b].setChoose('o');

				gameOver = 10;
				break;

			}

			i--;
			j--;

		}

		if (gameOver == 9 || gameOver == 10)   //en dÜstaki sonraki loop tan cÜkmak için(eger sart saglanÜrsa tabi)
			break;

		i = row - 1;  // i yi yine en alt satÜr alyyorum
		j = row - a;  //j'yi a kadar azaltÜyorum ki sola birer birer kaysyn hep

		a++;          // a'yÜ bir arttÜrÜyorum ki j istenilen degere ulassÜn ve en dÜstaki döngÌ kontrol edilsin diye

	}





	return gameOver;     //gameOver degiskenine dönderiyorum ki kimin yendigini daha sonra kontrol edebileyim


}
