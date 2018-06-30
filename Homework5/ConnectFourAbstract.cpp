
#include<iostream>
#include<string>
#include <cstdlib>
#include<ctime>
#include <fstream>

#include "ConnectFourAbstract.h"
#include "Cell.h"

using namespace std;

ConnectFourAbstract::ConnectFourAbstract() {

       
	temp.setColumnNames(); //otomatik atama yapilmis olacak o yüzden paramatre göndermiyorum
	setCounter(0);   //oyun sirasini tutacak olan fonksiyonuma ilk degerini initiliazed ediyorum

}

ConnectFourAbstract::ConnectFourAbstract(int row, int column,char mode) {

	setBoard( );   //boardumu ayarlamasi icin fonksiyonumu cagiriyorum


}

void ConnectFourAbstract::setBoard() {
 
	int row, column;       //hem playGame den hem de Constructordan cagrildigi icin inputlari burada aliyorum
	char mode;

	cout << "\n Enter row = ";
	cin >> row;

	cout << "\n Enter column = ";
	cin >> column;

	cout << "\n Enter game mode = ";
	cin >> mode;

	

	temp.setRow(row);         //aldigim ilk degerleri setters larla set ediyorum
	temp.setColumn(column);
	temp.setMode(mode);

       gameBoard = new Cell*[row];  //oyun boardunu tutmasi icin heapten iki boyutlu yer aliyorum
       moveOrder = new int*[row];     //hamle sirasini tutmasi icin heapten iki boyutlu yer aliyorum
		
       for (int i = 0; i < row; i++) {

	  gameBoard[i] = new Cell[column];
	  moveOrder[i] = new int[column];
		

	}

       for (int i = 0; i < row; i++)
	   for (int j = 0; j < column; j++)      //yukarda olusturdugum board icin ilk choose larini ayarliyorum
		gameBoard[i][j].setChoose('_');     


       for (int i = 0; i < row; i++)
	   for (int j = 0; j < column; j++)
		moveOrder[i][j] = 0;      //hamle dogrusunu dogru tutup kullanabilmek icin ilk degerlerini 0 a atiyorum
	



}

int ConnectFourAbstract::setCounter(int _counter) {
	counter = _counter;

	return counter;
}

int ConnectFourAbstract::play(string cellPosition) {

	
	int control = 0;
	int choose = 0;
	bool playerCh = false;
	int counter = getCounter();  //en sondaki siradan devam ettiriyorum ki hamle sirasini bileyim
	char mode = temp.getMode();  //gerekli bilgileri classdan cekiyorum
	int row = temp.getRow();
	int column = temp.getColumn();
	string columnName = temp.getColumnNames();
	string playerTurn = temp.getPlayerTurn();


	while (playerCh == false) {

	   control = 0;

	   for (int i = 0; i < column; i++) {

		if (cellPosition[1] == '\0') {     //girilen seyin char mi string mi olduguna bakiyorum
		     if (cellPosition[0] == columnName[i]) {
			  choose = i;
			  playerCh = true;
			  break;


		     }

		 if (cellPosition[0] != columnName[i])     //bu sarta bakarak control sayisini arttiriyorum ki altta kullanayim
		    control++;

		}


		else if (cellPosition[1] != '\0') {
		   oldBoard(cellPosition);  //girilen deger string ise load veya save oldugunu kontrol etmesi icin oldBoard a gonderdim
			
              }


	 }

		if (playerCh == true)
		  break;


		if (control == column) {     //control column sayisina esit oldugunda farkli bir harfle oynuyor demektir

                   if(cin.eof())    //yeni harf almadan once dosyadan input alinirsa diye kontrolumu yapiyorum
                       exit(1);		
                     	
                   cout << "\nPlease just try to play capital letters \n\n\t\t   which is shown upper  >> like capital A <<  = ";


                   if(!cin.eof())   //eger dosyadan okunuyorsa ve eof gelmediyse input aliyorum normal giristede calisir sonucta
		     cin >> cellPosition;
                         
                       
		 playerCh = false;         //yeni girisin kontrolu icin playerCh yi false yapiyorum

		}

		if (control != column && gameBoard[0][choose].getChoose() != '_') {
			// dolu bir yere oynarsa eÃ°er bu uyariyi versin diye ayarladim

			cout << "\n\nThe column which you are trying to play is full try another one please = ";
			
                        if(!cin.eof())   //hamle olmadan once dosya sonu gelmis mi kontrolumu yapiyorum
			cin >> cellPosition;  //gelmemisse hamle aliyorum
                         
                        else
                         exit(1);   //gelmisse sonsuz loop olmamasi icin oyunu bitiriyorum

			playerCh = false;         //false yaparak hamlesinin tekrar kontrolunu sagliyorum

		}

	

		if (cellPosition[1] != '\0' ) {
		  cout << "\n\n There is no match wtih your input >> " << cellPosition << " <<  try LOAD, SAVE, UNDO \n\t enter a new move = ";
		  cin >> cellPosition;
		  playerCh = false;      //eslesmeyen bir string giriyorsa yeniden input aliyorum

		}



	}

        



	for (int i = (row - 1); i >= 0; i--) {  //burada artik yukaridaki tum durumlari gecip gelmis bir durum icin hamle yaptiriyorum

		if (gameBoard[i][choose].getChoose() == '_') {
			//en alt satirdan baslayarak kontrol etmesini ve bos yer varsa X koymasini sagladim

			if (playerTurn == "player1") {  //oyun sirasi kimdeyse ona gore X veya O kordutmasini sagladim
				gameBoard[i][choose].setChoose('X');
				counter++;
				setCounter(counter);
				moveOrder[i][choose] = counter;

				return 0;

			}

			if (playerTurn == "player2") {
				gameBoard[i][choose].setChoose('O');
				counter++;
				setCounter(counter);
				moveOrder[i][choose] = counter;

				return 0;
			}


		}


	} //for un sonu


	cout << " make a legal move = ";  //aksi durumda legal hamle yapmasini istedim
	cin >> cellPosition;
	playerCh = false;



	return 0;    // fonkisyonu sonlandirdim

}

int ConnectFourAbstract::play() {


	int row = temp.getRow();
	int column = temp.getColumn();

	int check = 0;
	int z = 0;  // z  ve y yi random atama yaparken kullanacagim
	int y = 0;
	int check1 = 0;
	int f = 0;
	int checkMove = 0, checkMove1 = 0, checkMove2 = 0, checkMove3 = 0;
	bool gameover = false;
	bool randomVal = false;
	int livingCells = 0;

	
	while (gameover == false) {
		//oyunun istenilen yere kadar bitmemesi iÃ§in while loop kullandÃœm

	    srand(time(NULL));

	    for (int i = (row - 1); i >= 0; i--) {

	        for (int j = column - 1; j >= 0; j--) {

		    for (int x = row - 1; x >= 0; x--) {
			// 3 tane ic ice for kullnarak board'un en asagisina ve sagina gittim
			 // ve asagidan yukari dogru sutunlari kontrol ettim

			 if (gameBoard[x][j].getChoose() == 'X')
			//eger X ile karsilasilirsa daha onceden tanimladigim integeri arttirdim
			     checkMove++;                 

			 else if (gameBoard[x][j].getChoose() != 'X')
			  //X gormezse o ana kadar saydirdigim degerleri sifirliyorum
			     checkMove = 0;

			 if (checkMove <= 3 && x == 0)    // x bulundugu satir ve eger x=0 oldugunda checkMOve hala 3 olmamissa
			     checkMove = 0;      // bu daha da olamayacagi anlamina gelir o yuzden tekrar sifira atadim

			 if (gameBoard[x][j].getChoose() == 'O') // Ayni mantikla  O karakterini kontrol ettirdim
			  
			     checkMove3++;       // eger ust uste O ile karsilasirsa artacak surekli

			 else if (gameBoard[x][j].getChoose() != 'O')
			  // eger ust uste O gelmezse sifirliyorum ki diger satirda kaldigi yerden devam etmesin
			     checkMove3 = 0;               

			  if (checkMove3 <= 3 && x == 0)
			   //Ayni X icin oldugu gibi bu durum oldugunda daha 4 tane olamiyacagindan 0 liyorum
			     checkMove3 = 0;

			  if ((checkMove == 3 || checkMove3 == 3) && gameBoard[x - 1][j].getChoose() == '_') {
			   //YUkaridaki degerlerden herhangi biri 3 oldugunda yanina hamle yaptiriyorum ki yenmesin player
			      gameBoard[x - 1][j].setChoose('O');

			      counter++;
			      setCounter(counter);   //yaptigim hamleyi, hamle sirasini turmak icin counteru arttirip moveOrdera da atiyorum
			      moveOrder[x-1][j] = counter;
						
			      gameover = true;
			      return 0;      // bu sart gerceklesirse fonksiyona devam edip birden fazla hamle yapmasinin onune geciyorum

			   }

		}  // en icteki for'un sonu



	}  // 2. for'un sonu


	if (gameover == true)
	    return 0;  // olurda buraya kadar gelip fonksiyon sonlanmamÃœs olursa diye tekrar return ediyorum

	for (int b = 0; b <= row - 1; b++) { // en distaki for un icinde bu loop

	    if (gameBoard[i][b].getChoose() == 'X')
	
	        checkMove1++;     //usteki mantıkla aynı sekilde bu sefer yanyana olan X leri tutmasi icin sart koyup integer arttiriyorum

	    else if (gameBoard[i][b].getChoose() != 'X')  // X gelmediginde sifirliyorum ki bir sonraki durumu etkilemesin
		checkMove1 = 0;

	    if (checkMove1 <= 3 && b == row - 1)  //eger satir sonuna gelmisse ve tutulan deger 3 ten kucukse daha da 4 olamaz 0 liyorum
		checkMove1 = 0;      

	    if (gameBoard[i][b].getChoose() == 'O')   //ayni mantikla O karakterini kontrol ediyorum
		checkMove3++;

	    else if (gameBoard[i][b].getChoose() != 'O')
		checkMove3 = 0;

	    if (checkMove3 <= 3 && b == row - 1)   //ayni mantikla bir sonraki satiri etkilemesin diye sifirliyorum
		checkMove3 = 0;


	    if (checkMove1 == 3 || checkMove3 == 3) {  //herhangi biri 3  oldugunda hamle yapmasi icin sartimi olusturuyorum

		if (b + 1 <= row - 1) {       //sonucta 3 oldugundaki b degerinin bir fazlasÃœna hamle yapmasi lazim
					   //eger b+1 row dan fazla olursa program hata verir onun onune geciyorum

		    if (i == row - 1 && gameBoard[i][b + 1].getChoose() == '_') {

			gameBoard[i][b + 1].setChoose('O');
			//  b+1 bossa oraya hamle yaptiriyorum
			counter++;
			setCounter(counter);
			moveOrder[i][b + 1] = counter;

			gameover = true;
							

			return 0;       //computerMove fonksiyonundan cikartiyorum ki tekrar hamle yapmasin

		    }

		   else if (i != row - 1) {  // i !=row-1 ise hamle yapacagi yerin bir altini kontrol ettiriyorum

			if (gameBoard[i + 1][b + 1].getChoose() != '_' && gameBoard[i][b + 1].getChoose() == '_') {

			   gameBoard[i][b + 1].setChoose('O');  //eger bir alti bos degilse ve hamle yapacagi yer bos ise yaptiryorum
			   counter++;
			   setCounter(counter);
			   moveOrder[i][b + 1] = counter;

			   gameover = true;
							

			   return 0;      //hamle yapmissa tekrar yapmasin diye fonksiyonu sonlandiriyorum

			}

	 }

	}



		   if (b - 3 >= 0) {   // sagina hamle yapmasini saglamistim burada ise soluna yaptiriyorum

			if (i == row - 1 && gameBoard[i][b - 3].getChoose() == '_') {
			 // eger en alt satirda ise yapiyor

			   gameBoard[i][b - 3].setChoose('O'); //ayni sekilde b-3 ile 3 birim geriye gidip kontrol ettiriyorum
			   gameover = true;        //ve bossa hamle yaptiriyorum
			   counter++;
			   setCounter(counter);
			   moveOrder[i][b - 3] = counter;

			 return 0;

			}

			else if (i != row - 1) { //en alt satirda degilse hamle yapacagi yerin altini kontrol ettiriyorum

			   if (gameBoard[i + 1][b - 3].getChoose() != '_' && gameBoard[i][b - 3].getChoose() == '_') {

				gameBoard[i][b - 3].setChoose('O');
				//yukaridaki ayarlamalar saglaniyorsa  hamle yaptiriyorum
				counter++;
				setCounter(counter);
				moveOrder[i][b - 3] = counter;
				gameover = true;
								

			        return 0;  //hamle yapmissa tekrar yapmasini engelliyorum

			   }

			}  //else if in sonu

		  }   // b-3 >0 u kontrol eden if in sonu

		  if (gameBoard[i][b - 3].getChoose() != '_' || gameBoard[i][b + 1].getChoose() != '_')
			break;  //aksi saglanirsa  for loop undan cikariyorum



	} //checkMove1 integerini kontrol eden if yapÃœsÃœnÃœn sonu


    }  // 4.forun sonu(b nin tanimli oldugu)

     if (gameover == true)
	return 0;   // olurda gameover true olmus ve hala cikmamis olursa diye




}  // en dÃœstaki for loop 'un sonu


 //sol taraftan Ã§apraz kontrol

     int i = row - 1;  //degerleri asagida kullanmak icin declare ettim
     int j = 0;
     int a = 1;

     while (i >= 0) {   //en ust satira ciktiginda daha arama yapmamasi icin sart koydum

	while (j != (row - a)) {   // j yi a kadar azaltip kontrol ettiriyorum ki capraz olsun

	    if (gameBoard[i][j].getChoose() == 'X')   // her gordugunde x i sayacak
		checkMove2++;

	    else if (gameBoard[i][j].getChoose() != 'X')  // arka arkaya gelmedigini anladiginda sifirlayacak
		checkMove2 = 0;


	    if (checkMove2 <= 3 && i == 1) //3 ten kucuk oldugunda ve bastan 1. satir oldugunda artik capraz bakarsa hata verir
		checkMove2 = 0;// board boyutu belli oldugundan boardun disina cikar ve hata verir bu yuzden sifirladim

				
            if (gameBoard[i][j].getChoose() == 'O')
		checkMove3++;         // ayni sekilde O sayisini kontrol ettirdim

    	    else if (gameBoard[i][j].getChoose() != 'O')
 		checkMove3 = 0;                // arka arkaya gelmiyorsa sifirladim

	    if (checkMove3 <= 3 && i == 1)
		checkMove3 = 0;               //usteki sart gibi kontrol ettim boardun disina cikmamak icin


	    if ((checkMove2 == 3 || checkMove3 == 3) && i - 1 >= 0)
		//herhangi biri 3 oldugunda boardun disina cikarmadan bir altina ve hamle yapacagi yeri kontrol edip hamle yaptiriyorum
		 

	    if (gameBoard[i - 1][j + 1].getChoose() == '_' && gameBoard[i][j + 1].getChoose() != '_') {
		 gameBoard[i - 1][j + 1].setChoose('O');

		 gameover = true;
		 counter++;
		 setCounter(counter);
		 moveOrder[i - 1][j + 1] = counter;
		 
                 return 0;    //hamle yaptiginda fonksiyondan cikardim
	    
             }


        i--;   //sol tarafa capraz ilerlemesini saglamak icin i'yi azaltip j'yi arttiriyorum
	j++;


	}  //icteki while loop'unun sonu

	if (gameover == true)
	    return 0;


 a++;   //a yi her seferinde 1 arttirarak satir sayisi 0 dan kucuk olmadan donguden cikmasini sagladim (i< row-a  oldugundan)
 i = row - a;     //bir ust satira bakmasini sagladim ki tekrar capraz arayabilsin
 j = 0;        //j yi sifirladim ki bir ust satira ciktiginda en sagdan  yani boyut(row) kac ise oradan baslasÃœn kontrol etmeye



 }    //soldan capraz kontrol sonu



  i = row - 1;   // degerleri tekrar dÃŒzenleyip asagidaki loop icin gerekli ayarlari olusturuyorum
  a = 1;
  j = row - 1;



 //sag taraftan capraz kontrol balangici

   while (i >= 3) {   // i=3 oldugunda daha 3 tane capraz gelse bile hamle yapacak yer olmadÃœgÃœnda >= sarti koydum
				   // cunku o ana kadar geip 3 oldugunda 4  e bakmaz

	while (j >= a) {    // j yi capraz gidebilmesi icin her seferinde a dan buyuk olarak ayarliyorum


	     if (gameBoard[i][j].getChoose() == 'X')
		//arka arkaya bu geliyor mu anlamak icin yazdym
		 checkMove2++;


	     else if (gameBoard[i][j].getChoose() != 'X')
		//eger arka arkaya ayni sey gelirken birden bu gelirse sifirlasin diye olusturdum
		checkMove2 = 0;


	     if (gameBoard[i][j].getChoose() == 'O')
		checkMove3++;


	     else if (gameBoard[i][j].getChoose() != 'O')
		checkMove3 = 0;


	     if (checkMove2 == 3 || checkMove3 == 3) {

		 if (i - 1 >= 0)
		    if (gameBoard[i - 1][j - 1].getChoose() == '_'&& gameBoard[i][j - 1].getChoose() != '_') {

			gameBoard[i - 1][j - 1].setChoose('O');
			gameover = true;

			counter++;
			setCounter(counter);
			moveOrder[i - 1][j - 1] = counter;
			break;

						}
		     }

	 i--;
    	 j--;
 

	}


	a++;
	i = row - a;    // her seferinde satÃœrÃœ a kadar azaltarak aÃŸaÃ°Ãœdan yukraÃœ kontrol ettirdim
	j = row - 1;
			// Ã§apraz kontrol yapabilmesi iÃ§in tekrar deÃ°erini aynÃœ yaptÃœm( yukarda a dan bÃŒyÃŒk ise while salanacagÃœndan)



  }  // saÃ° tarfatan Ã§apraz kontrol   sonu



 // daha fazla aklli hamle yapmasini istemedim ki oynayan surekli yenilmesin zaten puanim kirilmisti daha onceki ondevde bu yuzden sanirim

  // o yuzden eger yukardaki sartlar gerceklesmezse asagidaki loop ile random bir sekilde bir yere O koymasini sagladim


    while (gameover == false) {

	for (int i = row - 1; i >= 0; i--)
	    if (gameBoard[i][y].getChoose() == '_')
		check1++;



	    if (check1 >= 1) {

		if (z == row - 1 && gameBoard[z][y].getChoose() == '_') {

		   gameBoard[z][y].setChoose('O');
		   gameover = true;
		   counter++;   //hamle yaptiginda hamle sirasini tutmak icin conteri bir arttrip moveOrder in ilgili kismina gonderiyorum
		   setCounter(counter);  // 1 arttirma sebebim en son hamle tutuluyordu zaten artirmazsam ustune yazilir eskisi gider
		   moveOrder[z][y] = counter;
					
		   return 0;

		}

		else if (z != row - 1 && gameBoard[z][y].getChoose() == '_' && gameBoard[z + 1][y].getChoose() != '_') {

		   gameBoard[z][y].setChoose('O');
		   gameover = true;
		 			
		   counter++;//hamle yaptiginda hamle sirasini tutmak icin conteri bir arttrip moveOrder in ilgili kismina gonderiyorum
		   setCounter(counter);  // 1 arttirma sebebim en son hamle tutuluyordu zaten artirmazsam ustune yazilir eskisi gider
		   moveOrder[z][y] = counter;

		   return 0;

		}

	        else {

		  gameover = false;
		  z = rand() % row;  //random sayilar uretip asagida kullanilmasini sagliyorum
		  y = rand() % row;

		}


	      }

	     else if (check1 == 0) {
		f = y;      //burasi dolu oldugundan onu f e atiyorum
		z = rand() % row;   

		while (y == f) {   //y f eesit olmadiginda cikacak buradan boylece bos yer bulma olasiligi artacak

		    srand(time(NULL));
		    y = rand() % row;
		    z = rand() % row;
		    gameover = false;



		} //while sonu

	     }  // else if sonu


       }  //gameover sonu

  }    //fonksiyonun basinda tanÃœmlanan gameover sonu


    return 0;


}

int ConnectFourAbstract::drawBoard() {

	int row = temp.getRow();

	int column = temp.getColumn();
	string columnName = temp.getColumnNames(); 



	cout << endl << endl;

	for (int i = 0; i < column; i++)
		cout << "  " <<columnName[i] << " ";   //sutunlari harflendiren kisim

	cout << endl << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {

			cout << "  " << gameBoard[i][j].getChoose() << " ";   //boardu getChoose ile alip cizdirdim
 
		}
		cout << endl << endl;
	}


	return 0;
}

int ConnectFourAbstract::playGame() {

	
	
      int checking = 0;      // checkGame 'in return ettigi degeri buna atamak iÃ§in olusturdum
      bool gameOver = false;
      string move;
      int object = 0;
      ifstream file;
	
      if(counter == 0)   //oyun basladiginda tek bir defa row,column,mode alinsin diye sart koydum (defalarca alinir yoksa)
        setBoard();

      char mode = temp.getMode();  //mode u declare ettim
	

	
      if (mode == 'C') {         //oynayanin bilgisayarla oynamayi secmesi halinde calisacak condition tanimladim

	  cout << endl << endl;
	  drawBoard();  //oynayanin oynayacagi yerleri gormesi icin boardu ekrana bastiracak fonksiyonumu cagirdim

	  while (gameOver == false) {

	    cout << "\nEnter your choose = ";
				
             if(!cin.eof())
	        cin >> move;
                         
             else{

                cout<<endl<<endl;
                exit(1);
             }

	     temp.setPlayerTurn("player1");
	    
	     play(move);
	     cout << endl << endl;
	     checking = checkGame();    //oyunu control ettiriyorum
				

	     if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

		cout << endl << endl;     //bu sartlarin gelmesini ancak ve ancak player1 kazanirsa gercekleseceginden oyunu sonlandiriyorum
		drawBoard();
		cout << "\n\nthe winner is player1111 \n\n ";

		gameOver = true;
		exit(1);


	      }

				
             else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    

		drawBoard();  //bu sartlarin gelmesini ancak ve ancak player1 kazanirsa gercekleseceginden oyunu sonlandiriyorum
		cout << "\n\nthe winner is COMPUTER \n\n "; 

		gameOver = true;
                exit(1);
		//oyunu bitiriyorum

	     }

	     if (gameOver == true) 
                 exit(1);

	     drawBoard();     // yeni board u cizdiriyorum

	     cout << "\nComputer is thinking " << endl;

	     play();  //bilgisayar hamlesi alÃœyorum

	     checking = checkGame();// oyunun bitip bitmedigini kontrol ediyorum

				//checking degerine gore kazanan varsa oyunu yine bitiryorum

	     if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

		drawBoard();
		cout << "\n\nthe winner is player1111 \n\n ";
		gameOver = true;
                exit(1);

	      }

	     else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o

		drawBoard();
		cout << "\n\nthe winner is COMPUTER \n\n ";
		gameOver = true;
                exit(1);

	     }

	     if (gameOver == true)
		exit(1);


	     drawBoard();
				
	}    // while loop' sonu


  }   // en dÃœstaki if sonu


    if (mode == 'P') {         // oynayanin iki kisilik oyunu oyun secmesi durumunda calisacak condition

	drawBoard();       //oynayanin hamle yapabilecegi yerleri gorebilmesi icin boardu ekrana basiyorum

        while (gameOver == false) {

	   cout << "\n\n player1 please play = ";

	   if(!cin.eof())  //dosyadan input alindiginda eof karakteri geleceginden sart koyup input aldim
	      cin >> move;
         
           else   //eof geldiginde programi sonlandirdim
              exit(1);

	   temp.setPlayerTurn("player1");
	   play(move);

	   cout << endl;
	   drawBoard();

	   checking = checkGame();    //oyunun bitip bitmedi?ini kontrol ettim


	   if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {
	       drawBoard();

// player1 in yenmesi durumunu kontrol edip programi sonlandirdim  yenmemisse bu sartin icine girmeyecek zaten program devam edecek

	       cout << "\n\n ----> THE WİNNER İS player1 <--- \n\n ";

	       gameOver = true;
		
               exit(1);

	   }

	   else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o

		drawBoard();
		cout << "\n\n----> THE WİNNER İS player2 <--- \n\n ";

		gameOver = true;
		
                exit(1);

	}



	cout << "\n\n player2 please play = ";

        if(!cin.eof())   //dosya sonunu kontrol ediyorum
	  cin >> move;
         
        else
         exit(1);
     
	temp.setPlayerTurn("player2");
	play(move);
	drawBoard();       //yeni boardu cizdirdim

	checking = checkGame();            //oyunun bitip bitmedigini tekrar kontrol ettim




	if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

		//yukaidaki ile ayni mantikla kontrol ediyorum
		drawBoard();           //yenen nasil yendgini gorsun diye ekrana cizdime fonkisyonunu cagiriyorum
		cout << "\n\n----> THE WİNNER İS player1 <--- \n\n ";

		gameOver = true;
                exit(1);
		
	}

	else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
																									  //oyun bitmiÃŸÃŸse programÃœ sonlandÃœrÃœyorum yine

		drawBoard();
		cout << "\n\n----> THE WİNNER İS player2 <--- \n\n ";

		gameOver = true;
                exit(1);
		

	}  //else if sonu



   }    //while loop u icin son

  }



  return 0;

}



