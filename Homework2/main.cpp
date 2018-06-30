//////////////////////// --------- AHMED DÖNMEZ  ------------////////////////////
///////////////////////////////////  ------  141024008 ------///////////////
/////////////////////////////////////////////---------    HOMEWORK-2 -----//////////////

 #include <iostream>
 #include <cstdlib>
 #include <string>
 #include <fstream>
 #include <ctime>

 using namespace std;


 char** setBoardSize(int size=4);       //girilen size doğrultusunda oyun board'unu oluşturacak fonksiyon icin default fonksiyon tanımı
                                         // defaultta 4 alma sebebim oyunun en az 4*4 boyutta oynanacak olmasi
 int playerMove(char**, int,const int&);   //oyuncunun hamlesinin dogrulugunu kontrol edip  board'un içine atayan fonksiyon
 int player2Move(char**, int,const int&);       //2 kişilik oyunda ikinci kişi için hamle takibi yapıp board'a işleyecek fonksiyon
 int drawBoard(char**,const int&, string);            //ekrana boardu cidirecek olan fonksiyon
 int computerMove(char**,const int&);         //bilgisayarın hamle yapmasını saglayacak olan fonksiyon   
 int connectFour(char**, int&, char&);   // diger fonksiyonlari kullanarak oyunu bitene kadar calistiracak olan fonksiyon
 int checkGame(char**,const int&);             // olusturduğum board'u kontrol edip oyunun bitip bitmediğinine karar verecek olan fonksiyon
 int checkBoard(char**, int&, char&, string);  // oynayanin klavyeden girdiği karakterin legal olup olmadığını kontrol edecek  
                                                    //olan fonksiyon
 char** oldBoard(char**, int&, char&, string);  //oyunu kaydedecek veya eski oyunu yukletecek fonksiyon




 int main()
 {

	int size = 0;      //oyun boyutunu atayacağım integer 
	char mode;       // oyunun bilgisayara karşı mı yoksa iki kişilk oyun mu oldugunu tutacak karakter

	cout << "    ________________________________________" << endl << endl;
	cout << "    | >>>>  WELCOME TO CONNECT FOUR   <<<< |" << "\t  ///// Ahmed Donmez -----" << endl;
	cout << "    ________________________________________" << "\t\t ----- 141024008 /////" << endl<< endl;


	cout << "Enter the size you want to play = ";
	cin >> size;        //kullanıcıdan oyun boyutunu alıyorum

	while ((size % 2) != 0) {      // girilen boyut çift değilse çift bir integer girilene kadar değer istiyorum
		
                cout << "\nEnter the size again to play >> SIZE MUST BE EVEN NUMBER <<  = ";
		cin >> size;


	}       //while sonu

	cout << "\nWhich one you want to play \n\n  Play computer(pvc)---->> C\n  Two person game(pvp) ---->> P =  ";
	cin >> mode;      // kullanıcıdan oyun seçimini alıyorum
 
        if(mode=='C' || mode== 'P')
         cout<<"\n To load or save game just write LOAD OR SAVE and click enter button \n\t then we will take txt name from you\n\n";
 

	decltype( setBoardSize(size)) board = setBoardSize(size);  //daha sonra silmek üzere heap'ten iki boyutlu array adresi  
                                                                       // alacak fonksiyonumu çağırıyorum

        
	connectFour(board, size, mode);   //tüm oyunun döndüğü fonksiyonumu çağırarak oyunu başlatıyorum


	return 0;         //oyun bittiğinde main başarıyla bitsin diye 0'a return ediyorum
  }

  char** setBoardSize(int size) {  // iki boyutlu array olusturup adresini döndüren fonksiyon

	char** board = new char*[size];   // iki boyutlu dizi arrayi olusturmak icin heap'ten adres aliyorum

	for (int i = 0; i < size; i++)
		board[i] = new char[size];            

	for (int i = 0; i < size; i++)      //for döngüsüne sokarak ilk değerlerini _ şeklinde atadım
		for (int j = 0; j < size; j++)
			board[i][j] = '_';

	return board;   //board'un adresine return ederek fonksiyonumu sonlandirdim
 }

 int playerMove(char** board, int choose,const int& size) {

    for (int i=size-1; i >= 0; i--) {  // oynayanin secmis oldugu sutunu kontrol etmesi için for loop oluşturdum

	if (board[i][choose] == '_') {    //en alt satırdan baslayarak kontrol etmesini ve bos yer varsa X koymasını sağladım
	   board[i][choose] = 'X';

	   break;     //X koyduktan sonra tekrar tekrar koymasın diye for loop'undan çıkardim
	}

	} //for un sonu


	return 0;    // fonkisyonun başarıyla sonlandırılmasını sağladim

 }       //playerMove fonksiyonunun sonu

 
  int player2Move(char** board, int choose,const int& size) {  //player2 icin hamle yapacak fonksiyon

	for (int i = size - 1; i >= 0; i--) {    //secilen sutunu yine tarayıp boş yer varsa O koymasini sağladim

	  if (board[i][choose] == '_') {   
	      board[i][choose] = 'O';

	     break;  // boş bulduğu yere hamle yaptıktan sonra ikinci hamleyi yapmaması için döngüden çıkardım

	}  

	}


	return 0;   //fonksiyonu başarı ile sonlandırdım
 } 

 int drawBoard(char** board,const int& size, string chooseCheck) { 

      cout << endl << endl; 

      for (int i = 0; i < size; i++) {

	cout << "  " << chooseCheck[i] << " ";  // oynayanin hamle yapabilmesi için sütunların basina harf yazdirdim
          
	}

	cout << endl << endl;

     for (int i = 0; i < size; i++) {     //olusturduğum iki boyutlu diziyi iki for loop kullanarak ekrana yazdırdım
	
        for (int j = 0; j < size; j++)
	    cout << "  " << board[i][j] << " ";

     cout << endl << endl;   //her satiri yazdırdıktan sonra iki boşluk birakip aşağı geçmesini sağladım 
	
      }  //for loop un sonu


	return 0;

}     //drawBoard fonksiyonunun sonu


 int computerMove(char** board,const int& size) {   //fonksiyon size i degistirmeyeceginden const olarak aldim

    int check = 0;
    int z = rand()%size ;  
    int y = rand()%size ; 
    int f = 0;
    int checkMove = 0, checkMove1 = 0, checkMove2 = 0, checkMove3 = 0;
    bool gameover = false;
    bool randomVal = false;


    while (gameover == false) { //oyunun istenilen yere kadar bitmemesi için while loop kullandım

	for (int i = (size - 1); i >= 0; i--) {

	   for (int j = size - 1; j >= 0; j--) {

		for (int x = size - 1; x >= 0; x--) {  // 3 tane iç içe for kullnarak board'un en asağısına ve sağına gittim   
                                                         // ve aşağıdan yukarı doğru sütunları kontrol ettim
		   if (board[x][j] == 'X')        //eğer X ile karşılasırsa daha önceden tanımladigim integeri arttırdım
		     checkMove++;                  // 3 tane üst üste X varsa sonucta burası 3 olacak

		   else if (board[x][j] != 'X')      //X görmezse o ana kadar saydigi değerleri sıfırlıyorum 
		     checkMove = 0;

       	           if (checkMove <= 3 && x == 0)    // X bulundugu satır ve eğer x=0 olduğunda checkMove hala 3 olmamıssa 
		     checkMove = 0;                  // bu daha da olamayacağı anlamına gelir o yüzden tekrar sifira atadım

		   if (board[x][j] == 'O')           // Aynı mantikla bu sefer O karakterini kontrol ettirdim
		     checkMove3++;                     // eger ust uste varsa burasi artacak sürekli

		   else if (board[x][j] != 'O')       // eğer O görmezse sıfırlıyorum ki diğer sutuna gectiginde 
		     checkMove3 = 0;                       // bıraktığı yerden başlamasın

		   if (checkMove3 <= 3 && x == 0)     //Aynı X de geçerli olduğu gibi satır 0 a gelidğinde hala 3 olmamıssa sıfırlıyorum
		     checkMove3 = 0;

		   if ((checkMove == 3 || checkMove3 == 3) && x-1>=0)     
                        if(board[x - 1][j] == '_') {   //yukarıdaki değerlerin herhangi biri 3 oldugunda 
		         board[x - 1][j] = 'O';         //hemen ustu bossa hamle yaptırıyorum
		         gameover = true;         
		          return 0;      // bu if gerçekleşirse fonksiyondan başarı ile cıkmasını sağlıyorum

		   }

	    }  // en içteki for'un sonu

		

	}  // 2. for'un sonu


		if (gameover == true) 
                       return 0;  // olurda buraya kadar gelip fonksiyon sonlanmamis olursa diye tekrar return ediyorum
                 
			for (int b = 0; b <= size - 1; b++) { // en distaki for içinde bu for loop'u
                          
                           if (board[i][b] == 'X')            //bu sefer yanyana olan X leri kontrol ediyorum
			     checkMove1++;        //üsteki mantıkla aynı olarak tanimlamis oldugum integer değerini arttırıyorum

			   else if (board[i][b] != 'X')        // X görmedğinde sıfırlıyorum    
                             checkMove1 = 0;

			   if (checkMove1 <= 3 && b == size - 1)  //eğer satırın sonuna gelmiş ve integer 3 ten küçük değer
			      checkMove1 = 0;                // tutuyorsa tekrar o satırda 3 olamaz sıfırlıyorum ki sonraki satırı etkilemesin
         
			   if (board[i][b] == 'O')   //aynı mantıkla O karakterini kontrol ediyorum
			      checkMove2++;

			   else if (board[i][b] != 'O')
			      checkMove2 = 0;

			   if (checkMove2 <= 3 && b == size - 1)   //aynı mantıkla bir sonraki satırı etkilemesin diye sıfırlıyorum
			      checkMove2 = 0;


		           if (checkMove1 == 3 || checkMove2 == 3) {  //herhangi biri üç oldugunda hamle yapması lazım
            
				if (b + 1 <= size - 1) {        //sonucta 3 oldugundaki b değerinin bir fazlasına hamle yapması lazım       
                                                                      //eğer b+1 row dan fazla olursa program hata verir onun önüne geçiyorum
				 
                                   if (i == size - 1 && board[i][b + 1] == '_') {      

				      board[i][b + 1] = 'O';    //  b+1 bossa oraya hamle yaptırıyorum
				      gameover = true;
			    	      return 0;              //computerMove fonksiyonundan cıkartıyorum tekrar hamle yapmasın diye
				
                                    }
                  
                                else if (i != size - 1) {  // i !=row-1 ise hamle yapacagı yerin bir altını kontrol ettiriyorum            

				    if (board[i + 1][b + 1] != '_' && board[i][b + 1] == '_') {        

					board[i][b + 1] = 'O';  //eğer bir altı boş değilse ve hamle yapacagi yer boş ise yaptırıyorum
					gameover = true;
					return 0;      //hamle yapmıssa fonksiyonu sonlandırıyorum

				     }

                                 }

			    }

					

			       if (b - 3 >= 0) {   // sagina hamle yapmasini sağlamıstım burada ise soluna yaptıryorum  

				  if (i == size - 1 && board[i][b - 3] == '_') {    // eğer en alt satirda ise yapıyor     

					board[i][b - 3] = 'O';   //aynı sekilde b-3 ile 3 birim geriye gidip kontrol ettiriyorum
					gameover = true;        //ve bossa hamle yaptırıyorum
					return 0;
					
                                  }

				else if (i != size - 1) {      //en alt satırda değilse hamle yapacagı yerin altını kontrol ettiriyorum 

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


	  }  // 4.forun sonu(b nin tanimli oldugu)

	    if (gameover == true)
	       return 0;   // olurda gameover true olmus ve hala cıkmamıs olursa diye




    }  // en dıstaki for loop 'un sonu

    checkMove1=0;   //asagida tekrar kullnamak icin degerleri 0 a atadim
    checkMove2=0;


      //sol taraftan çapraz kontrol

      int i = size - 1;  // bu değerleri asagıdaki yapmasini istediğim kontrol icin atadim
      int j = 0;
      int a = 1;

      while (i >= 0) {   //en üst satıra çıktıgında daha da arama yapmaması için 0 dan büyük olmalı

	while (j != (size - a)) {   // j yi a kadar azaltıp kontrol ettiriyorum ki çapraz olsun

	  if (board[i][j] == 'X')   // her gördüğü x i sayacak
	    checkMove1++;
	
          else if (board[i][j] != 'X')    // arka arkaya gelmediğini anladıgında sıfırlayacak
	    checkMove1 = 0;

	  if (checkMove1 <= 3 && i == 1)    //3 ten küçük oldugunda ve bastan 1. satır olduğunda artık çapraz bakarsa hata verir 
	    checkMove1 = 0;           // board boyutu belli oldugundan dısarı cıkar ve hata verir bu yüzden sıfırladım 

	  if (board[i][j] == 'O')
	    checkMove2++;         // aynı sekilde O sayısını kontrol ettirdim
	  
          else if (board[i][j] != 'O')
	    checkMove2 = 0;                // arka arkaya gelmiyorsa sıfırladım

	  if (checkMove2 <= 3 && i == 1)
	    checkMove2 = 0;               //üsteki sart gibi kontrol ettim boardun dısına cıkmamak için


	  if ((checkMove1 == 3 || checkMove2 == 3) && i - 1 >= 0)  //herhangi biri 3 oldugunda boardun dısına cıkarmadan
                                                                // bir altını ve hamle yapacagı yeri kontrol edip hamle yaptırıyorum
	     
              if (board[i - 1][j + 1] == '_' && board[i][j + 1] != '_') {
		  board[i - 1][j + 1] = 'O';

		   gameover = true;           

		   return 0;    //hamle yaptıgında fonksiyondan cıkardim
	     }


           i--;   //sol tarafa capraz ilerlemesini saglamak için i'yi azaltıp j'yi arttırıyorum
	   j++;


	  }  //içteki while loop'unun sonu

      if (gameover == true)
	  return 0;  


       a++;   //a yı her seferinde 1 arttırarak satır sayısının 0 dan küçük olmadan döngüden cıkmasını sagladım (i< size-a  oldugundan)
       i = size - a;     //bir üst satira çikmasini sagladim ki tekrar çapraz arayabilsin
       j = 0;        //j yi sıfırladım ki bir üst satıra cıktıgında en sagdan  yani boyut(size) kac ise oradan baslasın kontrol etmeye



	}    //soldan çapraz kontrol sonu



     i = size - 1;   // değerleri tekrar düzenleyip aşağıdaki loop için gerekli şartları olusturuyorum
     a = 1;
     j = size - 1;

     checkMove1=0;
     checkMove2=0;
           

     //sağ taraftan çapraz kontrol başlangıcı
		
     while (i >= 3) {   // i=3 oldugunda daha 3 tane çapraz gelse bile hamle yapacak yer olmadıgında >= sartı koydum
                          // >= cünkü o ana kadar gelip 3 oldugunda 4  e bakmaz
	  
          while (j >= a) {    // j yi çapraz gidebilmesi için her seferşnde a dan büyük olarak ayarlıyorum


	    if (board[i][j] == 'X')   //arka arkaya bu geliyor mu anlamak için yazdim
		checkMove1++;


	    else if (board[i][j] != 'X')    //eger arka arkaya ayni sey gelirken birden bu gelirse sifirlasin diye olusturdum
		checkMove1 = 0;


	    if (board[i][j] == 'O')
		checkMove2++;


	   else if (board[i][j] != 'O')
		checkMove2 = 0;


           if (checkMove1 == 3 || checkMove2 == 3) {   //herhangi biri3 olmussa hamle yaptirarak oynayanın 4 lemesini engelliyorum

		if (i - 1 >= 0)
		  if (board[i - 1][j - 1] == '_'&& board[i][j - 1] != '_') {

		      board[i - 1][j - 1] = 'O';
		      gameover = true;
		      return 0;

		   }
           }

           i--;
	   j--;


	}


	a++;
	i = size - a;    // her seferinde satırı a kadar azaltarak aşağıdan yukari kontrol ettirdim
        j = size - 1;   // çapraz kontrol yapabilmesi için tekrar değerini aynı yaptım( yukarda a dan büyük ise while saglanacagından)



      }  // sağ tarfatan çapraz kontrol   sonu




   //  en altta 0 ve row-1 arasinda kalan sag caprazlari degerlendirmek için

      i = size - 1;  //değerleri tekrar aşağıdaki loop için ayarlıyorum
      j = 1;
      a = 1;

      checkMove1=0;
      checkMove2=0;

      while (j != size && (size - a) >= 3) {   //j boyuta eşit değilse ve 3 den fazla yer fazla üstte kontrol ettiriyorum ki disari cikmasin

	while (j <= (size - 1)) {    // j'yi bu ifadeden küçük tutarak size içerisinde tutuyorum

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
		  return 0;
	      }

           }


	   i--;
	   j++;

	}


	i = size - 1;  // i'yi yine en alt satıra alıyorum
	j = a + 1;   // j'yi a kadar arttırıyorum ki saga birer birer kaysın
	a++;    // a'yı bir arttırıyorum ki j istenilen değere ulassın ve en dıstaki döngü kontrol edilsin diye

	
     }

  
  // daha fazla akllı hamle yapmasını istemedim ki oynayan sürekli yenilmesin

  // o yüzden eğer yukardaki şartlar gercekledmezse asagidaki loop ile random bir sekilde bir yere O koymasını sağladım

   
    while (gameover == false) {   

	for (int i = size - 1; i >= 0; i--){
	    if (board[i][y] == '_')
		check++;

             else 
                check=0;

             }
       

	  if (check >= 1) {

	     if (z == size - 1 && board[z][y] == '_') {

		 board[z][y] = 'O';
	 	 gameover = true;
		 return 0;

		}

	    else if (z != size - 1 && board[z][y] == '_' && board[z + 1][y] != '_') {

		 board[z][y] = 'O';
		 gameover = true;
		 return 0;

   	    }

	    else {
         
              gameover = false;
	      z = rand() % size;
	      y = rand() % size;
	  
            }


	}

	else if (check == 0) {
	   f = y;             //eger  hamle yapacagı  yerde bos yer yoksa f=y olacak
	   z = rand() % size;

          while (y == f ) {     //boylece bu loop ile f den farkli bir random y degeri dondermis olacagim tekrar
	  
          srand(time(NULL));
           z = rand() % size;
	   y = rand() % size;
	   gameover = false;

	  

	  } //while sonu

	}  // else if sonu


       }  //gameover sonu
 
    }    //fonksiyonun basinda tanımlanan gameover sonu


	return 0;

} //computerMove sonu


  int connectFour(char** board, int& size, char& mode) {

    srand(time(NULL));
    string chooseCheck = "ABCDEFGHIKLMNOPRSTUX"; // oyun boyutu max 20*20 olarak yazıyor bu yuzde 20 tane karaktertutan bir string olusturdum

    int checking = 0;      // checkGame 'in return ettiği değeri buna atamak için olusturdum
    bool gameOver = false;     //oyunu loop icerisinde dondermek icin olusturdum
    
    
    if (mode == 'C') {         //oynayanın bilgisayarla oynamayı seçmesi halinde çalısacak

      
      drawBoard(board, size, chooseCheck);  //oynayanın oynayacagı yerleri görmesi için ekrana yazdırma fonksiyonumu çağırdım

      while (gameOver == false) {

         
         cout << "\nEnter your move = ";
         auto choose = checkBoard(board, size, mode, chooseCheck);  //sectigi yerin legal olup olmadığını kontrol ediyorum
      
         cout << endl;   
    

         playerMove(board, choose, size);           // daha önceden olusturmus oldugum fonkiyonla player hamlesini yaptırıyorum

         cout << endl << endl;
         checking = checkGame(board, size);    //oyunu control ettiriyorum

         if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {
 
  	   cout << endl << endl;        //ÜSTEKİ DEĞERLER DÖNMÜSSE OYNAYAN KAZANMIS DEMEKETİR
	   drawBoard(board, size, chooseCheck);
	   cout << "\n\nthe winner is player \n\n ";

	   gameOver = true;
	              

         }

         else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	  
           drawBoard(board, size, chooseCheck);
	   cout << "\n\nthe winner is COMPUTER \n\n "; //BU DURUMDA DA BİLGİSAYAR KAZANMIS DEMEKTİR

	   gameOver = true; //oyunu bitirmek için gameOver i true yapiyorum
	          

      }

       if(gameOver==true){     // oyunun bitmesi durumunda heapten aldıgım yeri geri serbest bırakıyorum
        
         for(int i=0; i<size; i++)
           delete[] board[i];
    
         delete[] board;
         exit(1);

        }
    
       
      drawBoard(board, size, chooseCheck);       // yeni board u çizdiriyorum 

      cout<<"\nComputer is thinking to make move \n";
      computerMove(board, size);  //bilgisayar hamlesi alıyorum
     
      drawBoard(board, size, chooseCheck); //bilgisayar hamlesini oynayana gostermek icin board u cizdiriyorum

      checking = checkGame(board, size);// oyunun bitip bitmediğini kontrol ediyorum

        //checking değerine gre kazanan varsa oyunu yine bitiryorum

       if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

         drawBoard(board, size, chooseCheck);
         cout << "\n\nthe winner is player1111 \n\n ";

         gameOver = true;
         

       }

       else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	  
         drawBoard(board, size, chooseCheck);
	 cout << "\n\nthe winner is COMPUTER \n\n ";

	 gameOver = true;
         


	}
     
       if(gameOver==true){     // oyunun bitmesi durumunda heapten aldıgım yeri geri serbest bırakıyorum
        
         for(int i=0; i<size; i++)
           delete[] board[i];
    
        delete[] board;
        exit(1);    //ayrı ayrı iki defa yazma sebebim bir defa while loop tan cıkarıp yazdıgımda oyun bittiği halde oyunu bitrmemesi

    }



     }    // while loop' sonu




   }   // en distaki if sonu



    if (mode == 'P') {         // oynayanın iki kişilk oyun secmesi durumunda oyun oynatacak yapi için baslangic yaptım
  
      drawBoard(board, size, chooseCheck);    //oynayacak kişinin hamle yapabileceği yerleri görebilmesi için ekrana cizdirdim

      
      while (gameOver == false) {
       
        

        cout << "\n\n player1111 please play = ";
        auto choose = checkBoard(board, size, mode, chooseCheck);
           
        cout << endl << endl;
        playerMove(board, choose, size);      //1.oyuncunun hamlesi için fonksiyonumu çagırdım

        cout << endl;
        drawBoard(board, size, chooseCheck);

        checking = checkGame(board, size);    //oyunun bitip bitmedigini kontrol ettim


	if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {  
           
 // player1 in yenmesi durumunu kontrol edip programı sonlandırdım  yenmemisse bu yapi içine girmeyecek zaten progaram devam edecek
	  drawBoard(board, size, chooseCheck);
	  cout << "\n\nthe winner is player1111 \n\n ";
	 
          gameOver=true;
          exit(1);
	
        }
	
         else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	   
            drawBoard(board, size, chooseCheck);
	     cout << "\n\nthe winner is player22222 \n\n ";
  
             gameOver=true;
	     exit(1);

	 }
          
 
        
	 cout << "\n\n player2 please play = ";
	 choose = checkBoard(board, size, mode, chooseCheck);
        
	 cout << endl;

	 player2Move(board, choose, size);    //hamleyi kontrol edecek olan fonkisyonumu cagirdim
	 drawBoard(board, size, chooseCheck);           //yeni boardu çizdirdim
	 checking = checkGame(board, size);            //oyunun bitip bitmedigini tekrar kontrol ettim




	 if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {  

             //yukarıdaki ile aynı sekilde oyun kontrolü 
	     drawBoard(board, size, chooseCheck);       //yenen nasıl yendiğini görsün diye ekrana cizdime fonkisyonunu çağrıdım
	     cout << "\n\nthe winner is player1111 \n\n ";

             gameOver=true;
	     exit(1);

	  }
			
         else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
           //oyun bitmisse programı sonlandiriyorum yine		
		
             drawBoard(board, size, chooseCheck);
	     cout << "\n\nthe winner is player22222 \n\n ";
		 
            gameOver=true;		
            exit(1);

	  }  //else if sonu
         
        

      }   //while loop u için son

	
     }   // en dıstaki if için son
 

	for (int i = 0; i < size; i++)    // oyunun bitmesi durumunda daha önceden heap'den aldıgım yeri tekrar verdim
	      delete[] board[i];

	delete[] board;

	return 0;

 }  //connectFour fonksiyonu sonu


 int checkGame(char** board,const int& size) {

    int check[12]={0};
    int i = size - 1;
    int a = 1;
    int j = 0;
    int control=0;
    int gameOver = 0;
 

  //dikey  ve yanlamasına kontrol

    for (int i = (size - 1); i >= 0; i--) {  

       for (int j = (size - 1); j >= 0; j--) { 

	   for (int x = 0; x <= size - 1; x++) {   //computerMOve da oldugu gibi en alt satır ve stundan yukarı dogru kontrol ediyoum

		if ((board[x][j] == 'X'))     // X gördüğüm yerde daha önceden tanımladığım dizinin birinci elemanını arttırıyorum
		   check[0]++;

		if (board[x][j] != 'X')     //X görmediği zaman 0 lanıyor
		  check[0] = 0;

                 if(check[0]<=3 && x==size-1)    //eger bu durum gerceklernirse daha da aynı sutun uzerinde 4 tane ust uste gelmez
                   check[0]=0;             //ve bende bu sartı koydum kı asagıda harflerı kucultugumde board disina cıkıp hata vermesin

                if (board[x][j] == 'O')       //aynı sekilde O karakteri içinde kontrol ediyorum
		  check[1]++;
				
                else if (board[x][j] != 'O')    // O karkaterini görmediği zaman sıfırlanıyor
		  check[1] = 0;

                  if(check[1]<=3 && x==size-1)
                   check[1]=0;

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



	if (gameOver == 1 || gameOver==2)   // ilk for içindeki kısım saglanırsa artık geriye kalanları kontrol etmeden burdan dısarı aldım
           break;
			
	if (board[i][j] == 'X')     // bu sefer satır üzerinde yanyana X var mı kontrol ediyorum
	   check[2]++;

        if ((check[2]<= 3 && j == 0))   //j =0 oldugunda ve check[2]<=3 oldugunda artık 4 tane yanyana gelemeyiceğinden check[2] yi sıfıladım
	   check[2] = 0;

	else if (board[i][j] != 'X')   // X görmediği zaman sıfırladım
	   check[2] = 0;

        if (board[i][j] == 'O')     // O gördüğünden olusturdugum dizinin 4. elemanını arttırdım
	   check[3]++;

        if ((check[3] <= 3 && j == 0))      //üste yazdıgım gibi bu sart saglanıdgında daha 4 olma ihtimali yoktur
	   check[3] = 0;                       //program tekrar tekrar kontrol ettiğinde hep alt satırdan baslayacak alt satırdan
                                            //üst satıra aynı değerle giderse üst satırda 4 tane gelmeden oyunu bitirir 
                                          // o yüzden sıfırladım

     
	 if (board[i][j] != 'O')  //O görmezse sıfırlanacak
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
	return gameOver;          //oyun bitmisse fonksiyonu sonlandırıyorum

    if (gameOver == 3 || gameOver == 4)   //sondaki döngünün tekrarlanmasının önüne geciyorum yani
	return gameOver;

    }  // en dıştaki for için son


  
  //sol taraftan çapraz kontrol


    while (i >= 2) {   //2*2 ye geldğinde capraz arasada 4 olmaz o yüzden bu sartı koydum 2 ye esit olma sebibi 2 ye gelene
                         //kadar 2 olmussa 4 olma ihtimalini korumak için

	while (j != (size - a + 1)) {   //bu sartı koyarak capraz kontrol ederken sağa dogru sütun üzerinden gitme miktarını ayarladım
           if (board[i][j] == 'X')   //arka arkaya bu geliyor mu anlamak için yazdım
		check[4]++;
	   
           else if (board[i][j] != 'X')    //arka arkaya gelmiyorsa sıfırladım
		check[4] = 0;

           if(i<=2 && check[4] <=3 ) //2*2 boyutlarında aramaya geldiğinde artık 3 tane capraz olsada 4. olmayacagından sıfırladım
             check[4]=0;

	   if (board[i][j] == 'O')      //O için kontrol ettim
		check[5]++;
			
           else if (board[i][j] != 'O')      // arka arkaya gelmiyorsa sıfırladım
		check[5] = 0;

            if(i<=2 && check[5] <=3 )
              check[5]=0;



	   if (check[4] == 4) {          // olurda 4 tane X çapraz gelmişse gelen yerleri küçük x yaptım
		
              for (int b = 0; b <= 3; b++) 
		   board[i + b][j - b] = 'x';

             gameOver = 3;            //gameOver a tek sayı atadım
             return gameOver;        //oyun bitmisse sonlandiriyorum
	
            }

	    if (check[5] == 4) {    //eğer 4 tane O gelmişsse gelen yerleri küçük o ile değiştirdim 
		
               for (int b = 0; b <= 3; b++)      
		    board[i + b][j - b] = 'o';
		
               gameOver = 4;
	       return gameOver;    // oyun bitmisse direkt sonlandiriyorum
			
            }

        i--;   //sol tarafta en asagıdan baslayıp çapraz bakması için i'yi azaltıp j'yi arttırdım
        j++;


       }

      a++;   //a yı her seferinde 1 arttırarak satır sayısının 0 dan küçük olmadan döngüden cıkmasını sagladım( i< row-a  oldugundan)
      i = size - a;  //bir üst satıra çıkmasını sağladım  ki tekrar çapraz arayabilsin
      j = 0;           //j yi sıfırladım ki bir üst satıra cıktıgında en sagdan yani boyut kac ise oradan baslasın kontrol etmeye



     }   //sol taraftan capraz kontrol sonu



    i = size - 1;   //  degerleri eski haline dönderiyorum ki asagıdaki loop düzgün calıssın
    a = 1;
    j = size - 1;

    int b = 0;    //bir b intger'ı tanımladım

	
   //sag taraftan çapraz kontrol
	
    while (i >1) {   // en üst satıra cıktıktan sonra artık capraz aramamak için

      while (j >= (a - 1)) {   // sonucta 4 tane capraz olabilmesi için i=5 den baslıyorsa i=1 oldugunda j=5 olmalı o yüzden bu sartı koydum

	if (board[i][j] == 'X')  //arka arkaya bu geliyor mu anlamak için yazdım
	    check[6]++;

        else if (board[i][j] != 'X')     //gelmiyorsa sıfırladım
	    check[6] = 0;
         
       if (check[6]<3 && i < 2)   // bu sart saglandıgında kontrol etmesine gerek yok cünkü 4 tane arka arkaya olamayacak
	    check[6] = 0;            //kontrol ederse board disina cıkabilir

	if (board[i][j] == 'O')    // arka arkaya O geliyormu diye kontrol ettim
	    check[7]++;

	else if (board[i][j] != 'O')    // gelmiyorsa ddiye sıfırladım
	    check[7] = 0;

	if (check[7]<3 && i < 2)   // bu sart saglandıgında kontrol etmesine gerek yok cünkü 4 tane arka arkaya olamayacak
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
	   return gameOver;     //oyun bitmisse donguden cıkarıyorum cunku artık dıgerlerını kontrol etmeye gerek yok bu durumda

	a++;
	i = size - a;     //0. satıra geldiginde de loop'un devam etmmesi için bu degere atadım
	j = size - 1;     // sol çaprazdan en alt satırdan baslayp sütun sütun sola kayabilmesi için bu ifadeye atadım j'yi



    }  //sag tarfatan çapraz kontrol   sonu




  //  en altta 0 ve row-1 arasýnda kalan sag caprazlari degerlendirmek için

	i = size - 1;  //degerleri asagıdaki loop için tekrar ayarladim
	j = 1;
	a = 1;

	while (j != size && (size - a) >= 3) {   // j sütuna esit degilken ve en altta 3 tane gidecek yer kalmamıssa bunu yapmalı yoksa hata
                                                //yoksa board un dısına cıkacagından hata verir program

		while (j <= (size - 1)) {    //bunu kullanarak boyutu aşmanın önünde gectim

			if (board[i][j] == 'X')  //X görürse arttırmasın için olusturdum
			    check[8]++;

			else if (board[i][j] != 'X')        // arka arkaya gelmezse sıfırlasın diye olusturdum tekrar
			    check[8] = 0;
                      
                         if(check[8]<3 && j==size-2 ) //buraya geldiginde capraz bakmaya devam ederse board disina cikacagindan
                            check[8] = 0;     //ve board sınırlı sayıda yer ile oluturuldugundan hata verecekti bende bu sarti koydum ki
                                                   //bu durum gerceklendiginde board disina cikmasin
			if (board[i][j] == 'O')       // O gelirse diye
			    check[9]++;

			else if (board[i][j] != 'O')        //arka arkaya gelmezse diye bunu da sıfırladım
			    check[9] = 0;
 
                        if(check[9]<3 && j==size-2 )   //board disina cikmasini engelledim
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

		   i--;   // aradaki acigi capraz kontrol edebilmesi icin i'yi azaltıp j'yi arttiriyorum
		   j++;

	   }

	   if (gameOver == 7 || gameOver == 8)
		return gameOver;         //oyun bitmisse fonksyondan cikartıyorum diger sartlara bakmasina gerek yok cunku

	   i = size - 1;  // i yi yine en alt satır alıyorum
	   j = a + 1;   //j'yi a kadar arttırıyorum ki saga birer birer kaysın hep
	   a++;    // a'yı bir arttırıyorum ki j istenilen degere ulassın ve en dıstaki döngü kontrol edilsin diye


      }   // alt aciktaki sağ caprazlari bulan loop'un sonu



	i = size - 1;      // degerleri asagıdaki loop u dogru çalistirmak için tekrar degistirdim
	j = size - 2;
	a = 2;



	// en altta arada kalan sola dogru capraz kalan ayni hamleleri bulan kontrol loop'u


	while (j >= 2) {   //board'un dısına cıkmaması için gerekli kosullarımı loop'ların içerisinde tanımlıyorum

	   while (j >= 0 && i >= 1) {    //boyutu asmamak icin bu sartı yazdım

		if (board[i][j] == 'X') // 4 tane X yanyana gelme kontrolu
		   check[10]++;
		
                else if (board[i][j] != 'X')    //gelmemisse sifira atama      
		   check[10] = 0;   
            
                if(j<=1 && check[10] <3 )
                   check[10] = 0;            

		 if (board[i][j] == 'O')         //4 tane yanyana O gelme kontrolu
		   check[11]++;

		 else if (board[i][j] != 'O')     //gelmemisse sifira atiyorum
		   check[11] = 0;

                 if(j<=1 && check[11] <3 )
                   check[11] = 0;   

	         if (check[10] == 4) {  //4 tane X gelmişsse gelen yerleri küçük yaptım ki oynayan görsün

                      for (int b = 0; b <= 3; b++)
			  board[i + b][j + b] = 'x';
                            
                    gameOver = 9;
		    break;
 
		  }
			 
                  if (check[11] == 4) {  //4 tane O gelmisse onlari kucuk yaptım ki oynayan gorsun

		    for (int b = 0; b <= 3; b++)
			board[i + b][j + b] = 'o';
			
                    gameOver = 10;
		    break;

		  }

	    i--;
	    j--;

	 }

         if (gameOver == 9 || gameOver == 10)   //en dıstaki sonraki loop tan cıkmak için(eger sart saglanırsa tabi)
	    return gameOver; //sonucun digerlerini etkilememsi icin bu sart saglanırsa direkt sonlandiryorum fonksiyonu

	 i = size - 1;  // i yi yine en alt satır alýyorum
	 j = size - a;  //j'yi a kadar azaltıyorum ki sola birer birer kaysýn hep
		
          a++;          // a'yı bir arttırıyorum ki j istenilen degere ulassın ve en dıstaki döngü kontrol edilsin diye
       
	}



     control=0;   

     for(int i=0;i<=size-1;i++){        //en üsteki yani ilk satırı control ediyorum eğer row-1 olursa yer kalmamıs demektir
        if(board[0][i] != '_')
          control++;

          else if(board[0][i] == '_')
           control=0;

     }


    if(control==size) {    
       
       cout<<" \nThe board is full and no one is winner... \n\n";
       exit(1);
  }
    

	return gameOver;     //gameOver degiskenine dönderiyorum ki kimin yendigini daha sonra kontrol edebileyim

 }


 int checkBoard(char** board, int& size, char& mode, string chooseCheck) {  // oynayanin yaptigi hamlenin legal olmasini 
                                                                                      //saglayan fonksiyon

     string check;

     int control = 0;
     int choose = 0;
     bool playerCh = false;


     while (playerCh == false) {
	cin >> check;

	control = 0;

	for (int i = 0; i <= size; i++) {

	   if (check[1] == '\0') {
	      if (check[0] == chooseCheck[i]) {  //eger daha önce olusturdugum karkater dizinden bir karakter secmisse dogru oynamistir
		  choose = i;          //sectigi karakterin dizideki yerine bakip sayi olarak choose degiskenine atadim
		  return choose;

		}


	         else if (check[0] != chooseCheck[i])      //eger esit degilse bu control integer'ini arttirdim ki asagıya sart koydugumda
		     control++;                           //tekrar basa dönderip tekrar input alsin

	   }

	   else if (check[1] != '\0') {   //eger girilen string'in ikinci harfi varsa devamıda vardır diye dusunup
                                          //oldaBoard a gönderip kullanicinin istegini kontrol ettirdim
	      oldBoard(board, size, mode, check);
	    }


	}
          




	  if (control == size + 1) {     //control bu degere esit olmussa farkli karakterle oynuyor demektir
	    cout << "\nPlease just try to play capital letters \n\n\t\t   which is shown upper  >> like capital A <<  = ";
	    playerCh = false;         //yeni giris yapmasi için playerCh' yi false yaptim

	 }

	if (control != size + 1) {
             playerCh = true;           // esit degilse dogru karakter girmis o zaman playerCh true olur ve asagidaki sart saglanmazsa
									   //donguden cikar ve return choose olur
	}

	if (control != size + 1)
	  if (board[0][choose] != '_') {   // dolu bir yere oynarsa eðer bu uyarýyý versin diye ayarladým

		cout << "\n\nThe column which you are trying to play is full try another one please = ";
		playerCh = false;         //false yaparak tekrar hamle yapmasý için yukarý dönderdim

	   }


	}
       


	return choose;           //secim degerine döndererek fonkisyonumu sonlandýrdým

 }


 char** oldBoard(char** board, int& size, char& mode, string input) {  //girilen bir string'i okuyup LOAD VE SAVE komutlarini
                                                                      //gercekleyecek olan fonksiyon
      char check;
      string name;


      if (input == "SAVE") {     //SAVE GIRILMISSE KULLANICIDAN ISIM ALIP DOSAYAYA YAZDIRACAK KISIM

	cin.ignore();
	ofstream lastGame;
	cout << "Enter txt filename to save... :  ";
	getline(cin, name);      //getline ile txt ismini aldım
	lastGame.open(name.c_str(), ios::out);    //dosyaya yazdirabilmek için önce dosyayi actim

	if (lastGame.fail()) {
	   cerr << "Sorry the folder can not creating!!!\n "; //acılmazsa cerr objesine hata yukledim
           cerr << "try again later \n\n";

	}

	if (lastGame.is_open()) { //acilirsa row \n mode\n board olacak sekilde txt icine kaydettim oyunu

	  lastGame << size << endl << mode<< endl;


	   for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

		   lastGame << board[i][j] << endl;

		}

	    }


        cout << " \nThe board succesfuly saved \n\n You can play anytime you want \n\n ";
        cout  <<"if you want to continue playing enter any button" << endl;
	cout << " \n if you want to exit now enter ===>> Z = ";
	cin >> check;
	cout << endl << endl;

	}

	lastGame.close();  //txt yi kapattim

	if (check !='Z')    //oyunun devam etmesini saglayacak secim
	   connectFour(board, size, mode);

	if (check == 'Z')      //oyunu bitirecek secim
	    exit(1);
 
        
           

    }

     if (input == "LOAD") {        //LOAD KOMUTUNU CAGIRIRSA YUKLEYECEGI  OYUN ICIN TXT ISMI ALAN KISIM

	ifstream lastGame;
	cin.ignore();
	cout << "\n Enter the name of txt that you want to open =  ";
	getline(cin, name);

	lastGame.open(name.c_str(), ios::in);  //txt ismini kullanicinin sectigi sekilde ayarlıyorum burada

	if (lastGame.is_open()) {

            lastGame >> size >> mode ;  //eski oyunun boyutunu ve mode unu cagirip row ve mode u degistiryorum

	     board = setBoardSize(size);   //eski oyun size'i icin boardu ayarlayacak fonksiyonumu cagirdim
	     for (int i = 0; i < size; i++)
		 for (int j = 0; j < size; j++)
		     lastGame >> board[i][j];



	}

	if (lastGame.fail()) { //txt acilmazsa cerr ile hata mesaji veriyorum

	   cerr << "\nERROR NOT READING FILE !!! \nCHECK THE FILE THAT YOU IN ";
	   cerr << "\nThe game is continuing which is before you enter "<<input<<endl<<endl;
	    connectFour(board, size, mode);
		
         }

	 lastGame.close(); //txt yi kapatiyorum
	 cout << "\n The board is coming \n ";
	 cout << " Your last size = " << size;
	 
        
         if(mode=='C')
          cout<<"\n\nYou were playing with computer and we were taking your move \n\t\t so lets continue...:) ";

         if(mode=='P' )
           cout<<"\n\nYou were playing player to player game and we were taking your move \n so lets continue...:) ";

         connectFour(board, size, mode);

         
         }
        
        else{
          cout<<"if you try load or save game just write LOAD OR SAVE and click enter button \n\t then we will take txt name from you\n\n";
 
         cout<<"\n No operation is defined about "<<input<< "\nSo you are redirecting before you enter "<<input<<endl<<endl;
         connectFour(board, size, mode);

         }

        return board;
}
