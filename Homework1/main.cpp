//////////////////////// --------- AHMED DÖNMEZ  ------------////////////////////
///////////////////////////////////  ------  141024008 ------///////////////
/////////////////////////////////////////////---------    HOMEWORK-1 -----//////////////

 #include <iostream>
 #include <cstdlib>
 #include <string>

 using namespace std;


 char** setBoardSize(int*);       //girilen size doğrultusunda oyun board'unu oluşturacak fonksiyon
 int playerMove(char**, int, int);   //oyuncunun hamlesinin dogrulugunu kontrol edip  board'un içine atayan fonksiyon
 int player2Move(char**, int, int);       //2 kişilik oyunda ikinci kişi için hamle takibi yapıp board'a işleyecek fonksiyon
 int drawBoard(char**, int, char[]);            //ekrana boardu cidirecek olan fonksiyon
 int computerMove(char**, int);         //bilgisayarın hamle yapmasını saglayacak olan fonksiyon   
 int connectFour(char**, int, int);   // diğer fonksiyonları kullanarak oyunu bitene kadar çalıştıracak olan fonksiyon
 int checkGame(char**, int);             // oluşturduğum board'u kontrol edip oyunun bitip bitmediğinine karar verecek olan fonksiyon
 int checkBoard(char**, int, char[]);     // oynayanın klavyeden girdiği karakterin legal olup olmadığını kontrol edecek olan fonksiyon


 int main()
 {

	int row = 0;      //oyun boyutunu atayacağım integer 
	char** board;        // oyun boardunu olusturmak ve iki boyutlu array için adres döndermesi için pointer to pointer seklinde tanımladım
	int mode = 0;       // oyunun bilgisayara karşı mı yoksa iki kişilk oyun mu oldugunu tutacak integer

	cout << "    ___________________________________________ " << endl << endl;
	cout << "     >>>>  WELCOME TO CONNECT FOUR   <<<< " << "\t  ///// Ahmed Donmez" << endl;
	cout << "    ___________________________________________" << "\t\t 141024008 /////" << endl << endl;


	cout << "Enter the size you want to play = ";
	cin >> row;        //kullanıcıdan oyun boyutunu alıyorum

	while ((row % 2) != 0) {      // girilen boyut çift değilse çift bir integer girilene kadar değer istiyorum
		
                cout << "\nEnter the size again to play >> SIZE MUST BE ODD NUMBER <<  = ";
		cin >> row;


	}       //while sonu

	cout << "\nWhich one you want to play \n\n 1---->> play computer\n 2---->> two person game =";
	cin >> mode;      // kullanıcıdan oyun seçimini alıyorum

	cout << "\n\nYou have to play with capital letters so be sure that your caps lock is open \n";
         //oynayanı baştan uyarıyorum büyük harflerle oynaması için

	board = setBoardSize(&row);  //daha sonra silmek üzere heap'ten iki boyutlu array adresi alacak fonksiyonumu çağırıyorum


	connectFour(board, row, mode);   //tüm oyunun döndüğü fonksiyonumu çağırarak oyunu başlatıyorum


	return 0;         //oyun bittiğinde main başarıyla bitsin diye 0'a return ediyorum
  }

  char** setBoardSize(int* row) {  // iki boyutlu array olusturup adresini döndüren fonksiyon

	char** board = new char*[*row];   // iki boyutlu dizi arrayi olusturdum  için heap'ten adres alıyorum

	for (int i = 0; i < *row; i++)
		board[i] = new char[*row];            

	for (int i = 0; i < *row; i++)      //for döngüsüne sokarak ilk değerlerini _ şeklinde atadım
		for (int j = 0; j < *row; j++)
			board[i][j] = '_';

	return board;   //board'un adresine return ederek fonksiyonumu sonlandırdım
 }

 int playerMove(char** board, int choose, int row) {

    for (int i=row-1; i >= 0; i--) {  // oynayanın seçtiğolduğu sütunu kontrol etmesi için for loop oluşturdum

	if (board[i][choose] == '_') {    //en alt satırdan baslayarak kontrol etmesini ve bos yer varsa X koymasını sağladım
	   board[i][choose] = 'X';

	   break;     //X koyduktan sonra tekrar tekrar koymasın diye for loop'undan çıkardım
	}

	} //for un sonu


	return 0;    // fonkisyonun başarıyla sonlandırılmasını sağladım

 }       //playerMove fonksiyonunun sonu

 
  int player2Move(char** board, int choose, int row) {  //player2 için hamle yapacak fonksiyon

	for (int i = row - 1; i >= 0; i--) {    //seçilen sütunu yine tarayıp boş yer varsa O koymasını sağladım

	  if (board[i][choose] == '_') {   
	      board[i][choose] = 'O';

	     break;  // boş bulduğu yere hamle yaptıktan sonra ikinci hamleyi yapmaması için döngüden çıkardım

	}  

	}


	return 0;   //fonksiyonu başarı ile sonlandırdım
 } 

 int drawBoard(char** board, int row, char chooseCheck[]) { 

      cout << endl << endl; 

      for (int i = 0; i < row; i++) {

	cout << "  " << chooseCheck[i] << " ";  // oynayanın hamle yapabilmesi için sütunların basına harf yazdırdım
          
	}

	cout << endl << endl;

     for (int i = 0; i < row; i++) {     //olusturduğum iki boyutlu diziyi iki for loop kullanarak ekrana yazdırdım
	
        for (int j = 0; j < row; j++)
	    cout << "  " << board[i][j] << " ";

     cout << endl << endl;   //her satırı yazdırdıktan sonra iki boşluk bırakıp aşağı geçmesini sağladım 
	
      }


	return 0;

}     //drawBoard fonksiyonunun sonu

 int computerMove(char** board, int row) {

    srand(time(NULL));        //sürekli farklı sayılar döndürmesi için olsturdum  
    int check = 0;
    int z = rand()%row ;  // z ve y için boyutunu aşmayacak şekilde random sayı atadım
    int y = rand()%row ;
    int check1 = 0;
    int f = 0;
    int checkMove = 0, checkMove1 = 0, checkMove2 = 0, checkMove3 = 0;
    bool gameover = false;
    bool randomVal = false;


    while (gameover == false) { //oyunun istenilen yere kadar bitmemesi için while loop kullandım

	for (int i = (row - 1); i >= 0; i--) {

	   for (int j = row - 1; j >= 0; j--) {

		for (int x = row - 1; x >= 0; x--) {  // 3 tane iç içe for kullnarak board'un en asağısına ve sağına gittim   
                                                         // ve aşağıdan yukarı doğru sütunları kontrol ettim
		   if (board[x][j] == 'X')        //eğer X ile karşılasırsa daha önceden tanımladığım integeri arttırdım
		     checkMove++;                  // 3 tane üst üste X varsa sonucta burası 3 olacak

		   else if (board[x][j] != 'X')      //X görmezse o ana kadar saydığı değerleri sıfırlıyorum 
		     checkMove = 0;

       	           if (checkMove <= 3 && x == 0)    // x bulunduğu satır ve eğer x=0 olduğunda checkMOve hala 3 olmamıssa 
		     checkMove = 0;                  // bu daha da olamayacağı anlamına gelir o yüzden tekrar sıfıra atadım

		   if (board[x][j] == 'O')           // Aynı mantıkla X değil O karakterini kontrol ettirdim
		     checkMove3++;                     // eğer üst üste varsa burası artacak sürekli

		   else if (board[x][j] != 'O')       // eğer O görmezse sıfırlıyorum ki diğer sütuna geçtiğinde 
		     checkMove3 = 0;                       // bıraktığı yerden başlamasın

		   if (checkMove3 <= 3 && x == 0)     //Aynı X de geçerli olduğu gibi satır o a gelidğinde hala 3 olmamıssa sıfırlıyorum
		     checkMove3 = 0;

		   if ((checkMove == 3 || checkMove3 == 3) && board[x - 1][j] == '_') {      
                                             //yukarıdaki değerlerin herhangi biri 3 oldugunda hemen yanı bossa hamle yaptırıyorum
		     board[x - 1][j] = 'O';
		     gameover = true;         
		     return 0;      // bu if gerçekleşirse fonksiyondan başarı ile cıkmasını sağlıyorum

		   }

	    }  // en içteki for'un sonu

		   

	}  // 2. for'un sonu


		if (gameover == true)         
		   return 0;  // olurda buraya kadar gelip fonksiyon sonlanmamıs olursa diye tekrar return ediyorum

			for (int b = 0; b <= row - 1; b++) { // en dıstaki for içinde bu for loop'u
                          
                           if (board[i][b] == 'X')            //bu sefer yanyana olan X leri kontrol ediyorum
			     checkMove1++;        //üsteki mantıkla aynı olarak tanımlamıs oldugum integer değerini arttırıyorum

			   else if (board[i][b] != 'X')        // X görmedğinde sıfırlıyorum    
                             checkMove1 = 0;

			   if (checkMove1 <= 3 && b == row - 1)  //eğer satırın sonuna gelmiş ve integer 3 ten küçük değer
			      checkMove1 = 0;                // tutuyorsa tekrar o satırda 3 olamaz sıfırlıyorum ki sonraki satırı etkilemesin
         
			   if (board[i][b] == 'O')   //aynı mantıkla O karakterini kontrol ediyorum
			      checkMove3++;

			   else if (board[i][b] != 'O')
			      checkMove3 = 0;

			   if (checkMove3 <= 3 && b == row - 1)   //aynı mantıkla bir sonraki satırı etkilemesin diye sıfırlıyorum
			      checkMove3 = 0;


		           if (checkMove1 == 3 || checkMove3 == 3) {  //herhangi biri üç oldugunda hamle yapması lazım
            
				if (b + 1 <= row - 1) {        //sonucta 3 oldugundaki b değerinin bir fazlasına hamle yapması lazım       
                                                                      //eğer b+1 row dan fazla olursa program hata verir onun önüne geçiyorum
				 
                                   if (i == row - 1 && board[i][b + 1] == '_') {      

				      board[i][b + 1] = 'O';    //  b+1 bossa oraya hamle yaptırıyorum
				      gameover = true;
			    	      return 0;              //computerMove fonksiyonundan cıkartıyorum tekrar hame yapmasın diye
				
                                    }
                  
                                else if (i != row - 1) {  // i !=row-1 ise hamle yapacagı yerin bir altını kontrol ettiriyorum            

				    if (board[i + 1][b + 1] != '_' && board[i][b + 1] == '_') {        

					board[i][b + 1] = 'O';  //eğer bir altı boş değilse ve hamle yapacag yer boş ise yaptırıyorum
					gameover = true;
					return 0;      //hamle yapmıssa fonksiyonu sonlandırıyorum

				     }

                                 }

			    }

					

			       if (b - 3 >= 0) {   // sağına hamle yapmasına sağlamıstım burada ise soluna yaptıryorum  

				  if (i == row - 1 && board[i][b - 3] == '_') {    // eğer en alt satırda ise yapıyor     

					board[i][b - 3] = 'O';   //aynı sekilde b-3 ile 3 birim geriye gidip kontrol ettiriyorum
					gameover = true;        //ve bossa hamle yaptırıyorum
					return 0;
					
                                  }

				else if (i != row - 1) {      //en alt satırda değilse hamle yapacagı yerin altını kontrol ettiriyorum 

				   if (board[i + 1][b - 3] != '_' && board[i][b - 3] == '_') {   

					board[i][b - 3] = 'O';   //yukarıdaki şartları saglıyorsa  hamle yaptırıyorum
					gameover = true;
					return 0;  //hamle yapmıssa tekrar yapmasını engelliyorum

				   }

				 }  //else if in sonu

		               }   // b-3 >0 ı kontrol eden if in sonu
 
			       if (board[i][b - 3] != '_' || board[i][b + 1] != '_')
				  break;  //aksi sağlanırsa  for loop undan cıkarıyorum



		    } //checkMove1 integerini kontrol eden if yapısının sonu


	  }  // 4.forun sonu(b nin tanýmlý oldugu)

	    if (gameover == true)
	       return 0;   // olurda gameover true olmus ve hala cıkmamıs olursa diye




    }  // en dıstaki for loop 'un sonu



      //sol taraftan çapraz kontrol

      int i = row - 1;  // bu değerleri asagıdaki yapmasını istediğim kontrol için atadım
      int j = 0;
      int a = 1;

      while (i >= 0) {   //en üst satıra çıktıgında daha da arama yapmaması için o an büyük olmalı

	while (j != (row - a)) {   // j yi a kadar azaltıp kontrol ettiriyorum ki çapraz olsun

	  if (board[i][j] == 'X')   // her gördüğü x i sayacak
	    checkMove2++;
	
          else if (board[i][j] != 'X')    // arka arkaya gelmediğini anladıgında sıfırlayacak
	    checkMove2 = 0;

	  if (checkMove2 <= 3 && i == 1)    //3 ten küçük oldugunda ve bastan 1. satır olduğunda artık çapraz bakarsa hata verir 
	    checkMove2 = 0;           // board boyutu belli oldugundan dısarı cıkar ve hata verir bu yüzden sıfırladım şart sağlandığında

	  if (board[i][j] == 'O')
	    checkMove3++;         // aynı sekilde O sayısını kontrol ettirdim
	  
          else if (board[i][j] != 'O')
	    checkMove3 = 0;                // arka arkaya gelmiyorsa sıfırladım

	  if (checkMove3 <= 3 && i == 1)
	    checkMove3 = 0;               //üsteki sart gibi kontrol ettim boardun dısına cıkmamak için


	  if ((checkMove2 == 3 || checkMove3 == 3) && i - 1 >= 0)  //herhangi biri 3 oldugunda boardun dısına cıkarmadan
                                                                // bir altını ve hamle yapacagı yeri kontrol edip hamle yaptırıyorum
	     
              if (board[i - 1][j + 1] == '_' && board[i][j + 1] != '_') {
		  board[i - 1][j + 1] = 'O';

		   gameover = true;           

		   return 0;    //hamle yaptıgında fonksiyondan cıkardım
	     }


           i--;   //sol tarafa çapraz ilerlemesini saglamak için i'yi azaltıp j'yi arttırıyorum
	   j++;


	  }  //içteki while loop'unun sonu

      if (gameover == true)
	  return 0;  


       a++;   //a yı her seferinde 1 arttırarak satır sayısının 0 dan küçük olmadan döngüden cıkmasını sagladım (i< row-a  oldugundan)
       i = row - a;     //bir üst satrýa çýkmasýný saðladým ki tekrar çapraz arayabilsin
       j = 0;        //j yi sıfırladım ki bir üst satıra cıktıgında en sagdan  yani boyut(row) kac ise oradan baslasın kontrol etmeye



	}    //soldan çapraz kontrol sonu



     i = row - 1;   // değerleri tekrar düzenleyip aşağıdaki loop için gerekli şartları olusturuyorum
     a = 1;
     j = row - 1;


           
     //sağ taraftan çapraz kontrol başlangıcı
		
     while (i >= 3) {   // i=3 oldugunda daha 3 tane çapraz gelse bile hamle yapacak yer olmadıgında >=sartı koydum
                          // >= cünkü o ana kadar geip 3 oldugunda 4  e bakmaz
	  
          while (j >= a) {    // j yi çapraz gidebilmesi için her seferşnde a dan büyük olarak ayarlıyorum


	    if (board[i][j] == 'X')   //arka arkaya bu geliyor mu anlamak için yazdým
		checkMove2++;


	    else if (board[i][j] != 'X')    //eðer arka arkaya ayný sey gelirken birden bu gelirse sýfýrlasýn diye olusturdum
		checkMove2 = 0;


	    if (board[i][j] == 'O')
		checkMove3++;


	   else if (board[i][j] != 'O')
		checkMove3 = 0;


           if (checkMove2 == 3 || checkMove3 == 3) {

		if (i - 1 >= 0)
		  if (board[i - 1][j - 1] == '_'&& board[i][j - 1] != '_') {

		      board[i - 1][j - 1] = 'O';
		      gameover = true;
		      break;

		   }
           }

           i--;
	   j--;


	}


	a++;
	i = row - a;    // her seferinde satırı a kadar azaltarak aşağıdan yukraı kontrol ettirdim
        j = row - 1;    // çapraz kontrol yapabilmesi için tekrar değerini aynı yaptım( yukarda a dan büyük ise while salanacagından)



      }  // sağ tarfatan çapraz kontrol   sonu



       //  en altta 0 ve row-1 arasýnda kalan sað caprazlarý degerlendýrmek için

      i = row - 1;  //değerleri tekrar aşağıdaki loop için ayarlıyorum
      j = 1;
      a = 1;

      while (j != row && (row - a) >= 3) {   //j boyuta eşit değilse ve 3 den fazla yer fazla üstte kontrol ettiriyorum ki dısarı cıkmasın

	while (j <= (row - 1)) {    // j'yi bu ifadeden küçük tutarak size içerisinde tutuyorum

	   if (board[i][j] == 'X')          //aynı üstekiler gibi ve burada çaprazları kontrol ettiriyorum
	      checkMove1++;
		
	   else if (board[i][j] != 'X')
	       checkMove1 = 0;

	   if (board[i][j] == 'O')
	       checkMove2++;

	   else if (board[i][j] != 'O')
	       checkMove2 = 0;


	   if (checkMove1 == 3 || checkMove2 == 3) {  // 3 tane çapraz gelirse hamle yaptırıyoum

	      if (board[i - 1][j + 1] == '_' && board[i][j + 1] != '_') {
		  board[i - 1][j + 1] = 'O';

		  gameover = true;
		  break;
	      }

           }


	   i--;
	   j++;

	}


	i = row - 1;  // i'yi yine en alt satıra alıyorum
	j = a + 1;   // j'yi a kadar arttırıyorum ki saga birer birer kaysın
	a++;    // a'yı bir arttırıyorum ki j istenilen değere ulassın ve en dıstaki döngü kontrol edilsin diye

	
     }

  // daha fazla akllı hamle yapmasını istemedim ki oynayan sürekli yenilmesin

  // o yüzden eğer yukardaki şartlar gerçekleşmezse aşağıdaki loop ile random bir sekilde bir yere O koymasını sağladım

    while (gameover == false) {   

	for (int i = row - 1; i >= 0; i--)
	    if (board[i][y] == '_')
		check1++;



	  if (check1 >= 1) {

	     if (z == row - 1 && board[z][y] == '_') {

		 board[z][y] = 'O';
	 	 gameover = true;
		 return 0;

		}

	    else if (z != row - 1 && board[z][y] == '_' && board[z + 1][y] != '_') {

		 board[z][y] = 'O';
		 gameover = true;
		 return 0;

   	    }

	    else {
         
              gameover = false;
	      z = rand() % row;
	      y = rand() % row;
	  
            }


	}

	else if (check1 == 0) {
	   f = y;
	   z = rand() % row;

          while (y == f) {
	  
          srand(time(NULL));
	   y = rand() % row;
          z = rand() % row;
	   gameover = false;

	  

	  } //while sonu

	}  // else if sonu


       }  //gameover sonu
 
    }    //fonksiyonun basinda tanımlanan gameover sonu


	return 0;
} //computerMove sonu


  int connectFour(char** board, int row, int mode) {

  char chooseCheck[20] = { 'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','U','V' };   
  
  // oyun boyutu max 20*20 olarak yazdığından ödevde 20 harf tanımladım

    char check;
    int choose = 0;
    int checking = 0;      // checkGame 'in return ettiği değeri buna atamak için olusturdum
    bool gameOver = false;
    

    if (mode == 1) {         //oynayanın bilgisayarla oynamayı seçmesi halinde çalısacak


      drawBoard(board, row, chooseCheck);  //oynayanın oynayacagı yerleri görmesi için ekrana yazdırma fonksiyonumu çağırdım

      while (gameOver == false) {

      cout << "\nEnter your choose = ";
      choose = checkBoard(board, row, chooseCheck);  //seçtiği yerin legal olup olmadığını kontrol ediyorum

      cout << endl;   
    

      playerMove(board, choose, row);           // daha önceden olusturmus oldugum fonkiyonla player hamlesini yaptırıyorum
      cout << endl << endl;
      checking = checkGame(board, row);    //oyunu control ettiriyorum

      if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {
 
  	cout << endl << endl;        //ÜSTEKİ DEĞERLER DÖNMÜSSE OYNAYAN KAZANMIS DEMEKETİR
	drawBoard(board, row, chooseCheck);
	cout << "\n\nthe winner is player1111 \n\n ";

	gameOver = true;
	break;              //oyunu bitiriyorum

      }

      else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	drawBoard(board, row, chooseCheck);
	cout << "\n\nthe winner is COMPUTER \n\n "; //BU DURUMDA DA BİLGİSAYAR KAZANMIS DEMEKTİR

	gameOver = true;
	break;          //oyunu bitiriyorum

      }
       
      drawBoard(board, row, chooseCheck);       // yeni board u çizdiriyorum 

      computerMove(board, row);  //bilgisayar hamlesi alıyorum

      checking = checkGame(board, row);// oyunun bitip bitmediğini kontrol ediyorum
      drawBoard(board, row, chooseCheck);

        //checking değerine gre kazanan varsa oyunu yine bitiryorum

       if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

         drawBoard(board, row, chooseCheck);
         cout << "\n\nthe winner is player1111 \n\n ";

         gameOver = true;
         break;

       }

       else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	  
         drawBoard(board, row, chooseCheck);
	 cout << "\n\nthe winner is COMPUTER \n\n ";

	 gameOver = true;
         break;


	}
     if(checking==15){
           cout<<"the board is ful and no one wins \n";
           return 0;
      }



     }    // while loop' sonu




   }   // en dıstaki if sonu


    if (mode == 2) {         // oynayanın iki kişilk oyun secmesi durumunda oyun oynatacak yapı için baslangıc yaptım
  
      drawBoard(board, row, chooseCheck);    //oynayacak kişinin hamle yapabileceği yerleri görebilmesi için ekrana cizdirdim

      while (gameOver == false) {

        cout << "\n\n player1111 please play = ";
        choose = checkBoard(board, row, chooseCheck);
     
        cout << endl << endl;
        playerMove(board, choose, row);      //1.oyuncunun hamlesi için fonksiyonumu çaðýrdým

        cout << endl;
        drawBoard(board, row, chooseCheck);

        checking = checkGame(board, row);    //oyunun bitip bitmediðini kontrol ettim


	if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {  
           
 // player1 in yenmesi durumunu kontrol edip programı sonlandırdım  yenmemişşse bu ypaı içine girmeyecek zaten progaram devam edecek
	  drawBoard(board, row, chooseCheck);
	  cout << "\n\nthe winner is player1111 \n\n ";
	 
          gameOver=true;
          break;
	
        }
	
         else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	   
            drawBoard(board, row, chooseCheck);
	     cout << "\n\nthe winner is player22222 \n\n ";
  
             gameOver=true;
	     break;

	 }

            if(checking==15){
           cout<<"the board is ful and no one wins \n";
           gameOver=true;
           break;
      } 


	 cout << "\n\n player2 please play = ";
	 choose = checkBoard(board, row, chooseCheck);
	 cout << endl;

	 player2Move(board, choose, row);    //hamleyi kontrol edecek olan fonkisyonumu çaðýrdým
	 drawBoard(board, row, chooseCheck);           //yeni boardu çizdirdim
	 checking = checkGame(board, row);            //oyunun bitip bitmediðini tekrar kontrol ettim




	 if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {  

             //yukarıdaki ile aynı sekilde oyun kontrolü 
	     drawBoard(board, row, chooseCheck);       //yenen nasıl yendiğini görsün diye ekrana cizdime fonkisyonunu çağrıdım
	     cout << "\n\nthe winner is player1111 \n\n ";

             gameOver=true;
	     break;

	  }
			
         else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
           //oyun bitmişşse programı sonlandırıyorum yine		
		
             drawBoard(board, row, chooseCheck);
	     cout << "\n\nthe winner is player22222 \n\n ";
		 
            gameOver=true;		
            break;

	  }  //else if sonu


           if(checking==15){
           cout<<"the board is ful and no one wins \n";
           gameOver=true;
            break;
      }

      }   //while loop u için son

	
     }   // en dıstaki if için son
 

	for (int i = 0; i < row; i++)    // oyunun bitmesi durumunda daha önceden heap'den aldıgım yeri tekrar verdim
		delete[] board[i];

	delete[] board;

	return 0;
}


 int checkGame(char** board, int row) {

    int check[12]={0};
    int i = row - 1;
    int a = 1;
    int j = 0;
    int control=0;
    int gameOver = 0;
    int gameOver1 = 0;
    int d = row - 1;

  //dikey  ve yanlamasına kontrol

    for (int i = (row - 1); i > 0; i--) {  

       for (int j = (row - 1); j >= 0; j--) { 

	   for (int x = 0; x <= row - 1; x++) {   //computerMOve da oldugu gibi en alt satır ve stundan yukarı dogru kontrol ediyoum

		if ((board[x][j] == 'X'))     // X gördüğüm yerde daha önceden tanımladığım dizinin birinci elemanını arttırıyorum
		   check[0]++;

		if (board[x][j] != 'X')     //X görmediği zaman 0 lanıyor
		  check[0] = 0;

                if (board[x][j] == 'O')       //aynı sekilde O karakteri içinde kontrol ediyorum
		  check[1]++;
				
                else if (board[x][j] != 'O')    // O karkaterini görmediği zaman sıfırlanıyor
		  check[1] = 0;

                if (check[0] == 4) {  // eğer 4 olmussa dikey X'ler doğrultuda arka araya demektir oyunu bitirmek  
                                           //için gerekli komutları veriyorum

	           for (int c = 0; c <= 3; c++)
		      board[x - c][j] = 'x';        // en alt satırdan üste doğru okudugumdan 4 oldugu andaki x değerinden c cıkartarak
                                                        //4 defa ilerleyip hepsini küçük x ile değiştiriyorum
		   gameOver = 1;    //oyunu kimin bitridğini connectFour fonksiyonununda denetlemek için X yenerse tek, O yenerse çift 
		   break;         //olacak şekilde ayarlıyorum

		}

		 if (check[1] == 4) {
			
                    for (int c = 0; c <= 3; c++)
			board[x - c][j] = 'o';

		 gameOver = 2;    //check[1] 4 olursa bilgisayar kazanmıs demektir 
		 break;
				
                 }



	}  // en içteki for un sonu



	if (gameOver == 1)   // ilk for içindeki kısım saglanırsa artık geriye kalanları kontrol etmeden burdan dısarı aldım
           break;
			
	if (board[i][j] == 'X')     // bu sefer satır üzerinde yanyana X var mı kontrol ediyorum
	   check[2]++;

        if ((check[3]<= 3 && j == 0))   //j =0 oldugunda ve check[2]<=3 oldugunda artık 4 tane yanyana gelemeyiceğinden check[2] yi sıfıladım
	   check[2] = 0;

	else if (board[i][j] != 'X')   // X görmediği zaman sıfırladım
	   check[2] = 0;

        if (board[i][j] == 'O')     // O gördüğünden olusturdugum dizinin 4. elemanını arttırdım
	   check[3]++;

        if ((check[3] <= 3 && j == 0))      //üste yazdıgım gibi bu sart saglanıdgında daha 4 olma ihtimali yoktur
	   check[3] = 0;                       //program tekrar tekrar kontrol ettiğinde hep alt satırdan baslayacak alt satırdan
                                            //üst satıra aynı değerle giderse üst satırda 4 tane gelmeden oyunu bitirir 
                                           // o yüzden sıfırladım


	else if (board[i][j] != 'O')  //O görmezse sıfırlanacak
	   check[3] = 0;

	if (check[2] == 4) {          // eğer bu sart sagllanıyorsa ilgili yerleri küçük x ile değistirmeyi sagladıö

	  for (int b = 0; b <= 3; b++)
	      board[i][j + b] = 'x';


	  gameOver = 3;          // X kazandaıgında tek sayıya atamasını yapıyorum
	  break;   // loop tan cıkarıyorum sart saglanırsa
	
        }

	if (check[3] == 4) {         //aynı sekilde bu sefer O kazandıgında nasıl kazandığını göstermek için küçük o ile değisiyorum
	   
           for (int b = 0; b <= 3; b++)
	      board[i][j + b] = 'o';

	  gameOver = 4;
	  break;              // O kazandığından çift sayıya return edip oyunu sonlandırıyorum

        }



        }

    if (gameOver == 1 || gameOver == 2)    // yukardaki sartlar saglandıgında fonksiyondan tamamen cıkmasını saglıyorum
	break;

    if (gameOver == 3 || gameOver == 4)   //sondaki döngünün tekrarlanmasının önüne geciyorum yani
	break;

    }  // en dıştaki for için son


  
  //sol taraftan çapraz kontrol


    while (i >= 2) {   //2*2 ye geldğinde capraz arasada 4 olmaz o yüzden bu sartı koydum 2 ye esit olma sebibi 2 ye gelene
                         //kadar 2 olmussa 4 olma ihtimalini korumak için

	while (j != (row - a + 1)) {   //bu sartı koyarak capraz kontrol ederken sağa dogru sütun üzerinden gitme miktarını ayarladım
           if (board[i][j] == 'X')   //arka arkaya bu geliyor mu anlamak için yazdım
		check[4]++;
	   
           else if (board[i][j] != 'X')    //arka arkaya gelmiyorsa sıfırladım
		check[4] = 0;

	   if (board[i][j] == 'O')      //O için kontrol ettim
		check[5]++;
			
           else if (board[i][j] != 'O')      // arka arkaya gelmiyorsa sıfırladım
		check[5] = 0;

	   if (check[4] == 4) {          // olurda 4 tane X çapraz gelmişse gelen yerleri küçük x yaptım
		
              for (int b = 0; b <= 3; b++) 
		   board[i + b][j - b] = 'x';

             gameOver = 3;            //gameOver a tek sayı atadım
             break;        //döngüden cıkardım
	
            }

	    if (check[5] == 4) {    //eğer 4 tane O gelmişsse gelen yerleri küçük o ile değiştirdim 
		
               for (int b = 0; b <= 3; b++)      
		    board[i + b][j - b] = 'o';
		
               gameOver = 4;
	       break;
			
            }

        i--;   //sol tarafta en asagıdan baslayıp çapraz bakması için i'yi azaltıp j'yi arttırdım
        j++;


       }

      a++;   //a yı her seferinde 1 arttırarak satır sayısının 0 dan küçük olmadan döngüden cıkmasını sagladım( i< row-a  oldugundan)
      i = row - a;  //bir üst satıra çıkmasını sağladım  ki tekrar çapraz arayabilsin
      j = 0;           //j yi sıfırladım ki bir üst satıra cıktıgında en sagdan yani boyut kac ise oradan baslasın kontrol etmeye



     }   //sol taraftan capraz kontrol sonu



    i = row - 1;   //  degerleri eski haline dönderiyorum ki asagıdaki loop düzgün calıssın
    a = 1;
    j = row - 1;

    int b = 0;    //bir b intger'ı tanımladım

	
   //sag taraftan çapraz kontrol
	
    while (i >3) {   // en üst satıra cıktıktan sonra artık capraz aramamak için

      while (j >= (a - 1)) {   // sonucta 4 tane capraz olabilmesi için i=5 den baslıyorsa i=1 oldugunda j=5 olmalı o yüzden bu sartı koydum

	if (board[i][j] == 'X')  //arka arkaya bu geliyor mu anlamak için yazdım
	    check[6]++;

        else if (board[i][j] != 'X')     //gelmiyorsa sıfırladım
	    check[6] = 0;

	if (board[i][j] == 'O')    // arka arkaya O geliyormu diye kontrol ettim
	    check[7]++;

	else if (board[i][j] != 'O')    // gelmiyorsa ddiye sıfırladım
	    check[7] = 0;

	if (check[7]< 2 && i >= 2)   // bu sart saglandıgında kontrol etmesine gerek yok cünkü 4 tane arka arkaya olamayacak
	    check[7] = 0;

	if (check[6] == 4) {      //4 tane X ilen yeri küçük x ile değiştiriyorum

       	  for (int b = 0; b <= 3; b++) {

		board[i + b][j + b] = 'x';
				
          }

          gameOver = 5;   // X geldği için tek sayıya atıyorum
          break;  // döngüden cıkmasını saglıyorum

	 }

	 if (check[7] == 4) {       // 4 tane O gelmişşse onları küçük o ile değiştiriyorum

           for (int b = 0; b <= 3; b++) {

	    board[i + b][j + b] = 'o';
				
           }   

           gameOver = 6;    //çift sayıya atıyorum
	   break; //döngüden cıkartıyorum
	 
         }


	 i--;
	 j--;


	}

	if (gameOver == 5 || gameOver == 6)
	   break;

	a++;
	i = row - a;     //0. satıra geldiginde de loop'un devam etmmesi için bu degere atadım
	j = row - 1;     // sol çaprazdan en alt satırdan baslayp sütun sütun sola kayabilmesi için bu ifadeye atadım j'yi



    }  //sag tarfatan çapraz kontrol   sonu



	   //  en altta 0 ve row-1 arasýnda kalan sag caprazları degerlendirmek için

	i = row - 1;  //degerleri asagıdaki loop için tekrar ayarladım
	j = 1;
	a = 1;

	while (j != row && (row - a) >= 3) {   // j sütuna esit degilken ve en altta 3 tane gidecek yer kalmamıssa bunu yapmalı yoksa hata
                                                //yoksa board un dısına cıkacagından hata verir program

		while (j <= (row - 1)) {    //bunu kullanarak boyutu aşmanın önünde gectim

			if (board[i][j] == 'X')  //X görürse arttırmasın için olusturdum
			    check[8]++;

			else if (board[i][j] != 'X')        // arka arkaya gelmezse sıfırlasın diye olusturdum tekrar
			    check[8] = 0;

			if (board[i][j] == 'O')       // O gelirse diye
			    check[9]++;

			else if (board[i][j] != 'O')         //arka arkaya gelmezse diye bunu da sıfırladım
			    check[9] = 0;


			if (check[8]== 4) {  // 4 tane gelirse oyunun bitmesini saglamak için gerekli gameOver sayısını alıyorum

				for (int b = 0; b <= 3; b++)
				   board[i + b][j - b] = 'x';  // 4 olan yerleri kucuk x yapıyorum

			  gameOver = 7; //X geldigi icin tek sayıya atıyorum
			  break;

			}

			if (check[9] == 4) {  // O gelmisse eğer 4 defa gelen yerleri kucuk yapıyorum

			   for (int b = 0; b <= 3; b++)
				board[i + b][j - b] = 'o';

			  gameOver = 8;     //cift degere atıyorum 
			  break;           // loop tan cıkarıyorum

			}

		   i--;   // aradki acıgı capraz kontrol edebilmesi icin i'yi azaltıp j'yi arttırıyorum
		   j++;

	   }

	   if (gameOver == 7 || gameOver == 8)
		break;         //oyun bitmisse looptan cıkartıyorum

	   i = row - 1;  // i yi yine en alt satır alıyorum
	   j = a + 1;   //j'yi a kadar arttırıyorum ki saga birer birer kaysın hep
	   a++;    // a'yı bir arttırıyorum ki j istenilen degere ulassın ve en dıstaki döngü kontrol edilsin diye


      }   // alt acıktaki sağ caprazları bulan loop'un sonu



	i = row - 1;      // degerleri asagıdaki loop u dogru çalıstırmak için tekrar degistirdim
	j = row - 2;
	a = 3;



	// en altta arada kalan sola dogru capraz kalan aynı hamleleri bulan kontrol loop'u


	while (j >= 2) {   //board'un dısına cıkmaması için gerekli kosullarımı loop'ların içerisinde tanımlıyorum

	   while (j >= 0 && i >= 0) {    //boyutu asmamak icin bu sartı yazdım

		if (board[i][j] == 'X') // 4 tane X yanyana gelme kontrolu
		   check[10]++;
		
                else if (board[i][j] != 'X')    //gelmemisse sıfıra atama      
		   check[10] = 0;                       

		 if (board[i][j] == 'O')         //4 tane yanyana O gelme kontrolu
		   check[11]++;

		 else if (board[i][j] != 'O')     //gelmemısse sıfıra atama
		   check[11] = 0;


	         if (check[10] == 4) {  //4 tane X gelmişsse gelen yerleri küçük yaptım ki oynayan görsün

                      for (int b = 0; b <= 3; b++)
			  board[i + b][j + b] = 'x';
                            
                    gameOver = 9;
		    break;
 
		  }
			 
                  if (check[11] == 4) {  //4 tane O gelmisse onları kucuk yaptım ki oynayan gorsun

		    for (int b = 0; b <= 3; b++)
			board[i + b][j + b] = 'o';
			
                    gameOver = 10;
		    break;

		  }

	    i--;
	    j--;

	 }

         if (gameOver == 9 || gameOver == 10)   //en dıstaki sonraki loop tan cıkmak için(eger sart saglanırsa tabi)
	    break;

	 i = row - 1;  // i yi yine en alt satır alýyorum
	 j = row - a;  //j'yi a kadar azaltıyorum ki sola birer birer kaysýn hep
		
          a++;          // a'yı bir arttırıyorum ki j istenilen degere ulassın ve en dıstaki döngü kontrol edilsin diye
       
	}


     for(int i=0;i<row-1;i++){        //en üsteki yani ilk satırı control ediyorum eğer row-1 olursa yer kalmamıs demektir
        if(board[0][j] != '_')
          control++;

          else
           control=0;

     }


  if(control==row-1)      //bu durumda gameOver a bir değer atıyorum
   gameOver=15;
    

	return gameOver;     //gameOver degiskenine dönderiyorum ki kimin yendigini daha sonra kontrol edebileyim

}


  int checkBoard(char** board, int row, char chooseCheck[]) {  // oynayanın yaptığı hamlenin legal olmasını sağlayan fonksiyon

    char check;
    int control = 0;
    int choose = 0;
    bool playerCh = false;

    while (playerCh == false) {

       cin >> check;

	control = 0;

	for (int i = 0; i <= row; i++) {  
          
	   if (check == chooseCheck[i]) {   //eğer daha önce olusturdugum karkater dizinden bir karakter secmişşse doğru oynamıstır
		choose = i;          //sectiği karakterin dizideki yerine bakıp sayı olarak choose değikenine atadım
				
                break;
			
           }

	    else if (check != chooseCheck[i])      //eğer eşit değilse bu control integer'ını arttırdım
		control++; 

	 }


	 if (control == row + 1) {     //control bu değere eşit olmussa farklı karakterle oynuyor demektir
	   cout << "\nPlease just try to play capital letters \n\n\t\t   which is shown upper  >> like capital A <<  = ";
	   playerCh = false;         //yeni giriş yapması için playerCh' yi false yaptım

	  }

          if (control != row + 1) {
	     playerCh = true;           // eşit değilse doğru karakter girmiş o zaman playerCh true olur ve asağıdaki sart saglanmazsa
                                       //döngüden cıkar ve return choose olur
	  }
	
          if (control != row + 1)
	    if (board[0][choose] != '_') {   // dolu bir yere oynarsa eğer bu uyarıyı versin diye ayarladım
		
                 cout << "\n\nThe column which you are trying to play is full try another one please = ";
		  playerCh = false;         //false yaparak tekrar hamle yapması için yukarı dönderdim

	     }


	  }


	return choose;           //secim değerine döndererek fonkisyonumu sonlandırdım

}
