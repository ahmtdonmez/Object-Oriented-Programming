
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;


class ConnectFour {

public:
	ConnectFour();
	ConnectFour(int, int);
	ConnectFour(ifstream&);
	void setGame(ifstream&, int,int, char, int);
	int play(string, string, int);   //oyuncunun hamlesinin dogrulugunu kontrol edip  board'un iÃ§ine atayan fonksiyon
	int play(int);         //bilgisayarÃœn hamle yapmasÃœnÃœ saglayacak olan fonksiyon   
	int drawBoard(int);            //ekrana boardu cidirecek olan fonksiyon
	int playGame(char);		 //single time icin calÄ±sacak fonksiyon
	int checkGame(int);            // olusturdugum board'u kontrol edip oyunun bitip bitmediÃ°inine karar verecek olan fonksiyon
        int getInputs(ifstream&);
	int oldBoard(string, int); //LOAD ve SAVE komutlarÄ± geldiginde calÄ±sacak fonksiyon
	
	void setMultipleObject();      //multiple oyun icin objeleri alÄ±p olusmasÄ± icin gerekli komutlarÄ± verecek fonksiyon
	
        int readFromFile(ifstream&, string, char, char);




private:
	class Cell {
	public:
		Cell();
		int setRow(int);
		int setColumn(int);
		void setChoose(char);
		char setMode(char);
		string setChooseCheck(string);
		char setGameMode(char);
                int* setRowSpaces(int, int);
                int* setColumnSpaces(int, int);
                void setSpaces();  //bosuluklari tutan arrayler icin ilk atama yapılacak fonksiyon
		char  getChoose()const { return choose; }
		int getRow()const { return row; }
		int getColumn()const { return column; }
		char getMode()const { return mode; }
                int* getRowSpaces(){return rowSpaces;}
                int* getColumnSpaces(){return columnSpaces;}
		char getGameMode()const { return gameMode; }
		string getChooseCheck()const { return chooseCheck; }
		int setLivingCells(int);
		static int getLivingCells() { return livingCells; }

	private:

		int row;
		int column;
		char choose;
		char mode;
		string chooseCheck;
		static int livingCells;
		char gameMode; // single veya multiple oyunu gostrecek char tanýmladým
                int rowSpaces[];
                int columnSpaces[];

	};



	Cell temp2;
	Cell** gameBoard;
	ConnectFour* multipleObject;

};

int ConnectFour::Cell::livingCells;     //static membera erismek icin dÄ±sardan bunu tanimladim

ConnectFour::ConnectFour() {     //eger 0 parametre ile olusturulursa nesne minimum sartlarÄ± olusturmasÄ± icin olusturdum
	temp2.setRow(5);
	temp2.setColumn(5);
	temp2.setChooseCheck("ABCDEFGHIKLMNOPRSTUVYZ");
        
        
        
}

ConnectFour::ConnectFour(int row, int column) {
	 
    
    
	multipleObject = new ConnectFour[5];
	
	for (int a = 0; a < 5; a++) {
	   multipleObject[a].gameBoard = new Cell*[row];
		for (int i = 0; i < row; i++) {

		 multipleObject[a].gameBoard[i] = new Cell[column];
		}

	}

	
	

}

ConnectFour::ConnectFour(ifstream& fileName) {  //multiple oyun oynanacagÄ± zaman cagrilacak fonksiyon


 for(int i=1;i<=6;i++)
   multipleObject= new ConnectFour[5];
 

 
 getInputs(fileName);
 

}

ConnectFour::Cell::Cell() {
	//bile bile bos bÄ±raktÄ±m cunku bisey yapmasÄ±nÄ± istemiyorum

}



int ConnectFour::getInputs(ifstream& file){
    
    string boardName;
    char mode;
    char gameMode;
    
   gameMode=temp2.getGameMode(); 
    
  if(gameMode != 'M' && gameMode != 'S'){  
    
  cout<<"\nEnter board file name = ";
  cin>> boardName;
  
  cout<<"\n Enter mode( P OR C) = ";
  cin>> mode; 
  
  cout<<"\nEnter game Mode = ";
  cin>>gameMode;
 
  temp2.setGameMode(gameMode);
  readFromFile(file, boardName, mode, gameMode);
  }
    
}

void ConnectFour::setGame(ifstream& File, int row,int column, char mode, int object) {

    
    
	multipleObject[object].temp2.setRow(row);  //objeye gelen degiskenlerimi atÄ±yorum
      
	multipleObject[object].temp2.setColumn(column);
	multipleObject[object].temp2.setMode(mode);

	
	multipleObject[object].temp2.setChooseCheck("ABCDEFGHIKLMNOPRSTUVYZ");
	multipleObject[1].temp2.setLivingCells(0);
        
         for (int i = 0; i < row; i++)     //boardu dÃŒzgÃŒn gÃ¶zÃŒkmesi icin boardaki heryere _ karakterini atÄ±yorum
	    for (int j = 0; j < column; j++)
                if(multipleObject[object].gameBoard[i][j].getChoose() != '_')
	              multipleObject[object].gameBoard[i][j].setChoose(' ');
                     

	
}

int ConnectFour::readFromFile(ifstream& file, string boardName, char mode, char gameMode){
    

  int row;
  int column;
  int countColumn;
  string board;
  int check=1;
  bool game=false;
  int checkRow=1;
  int count=1;
 
  int checkColumn=0;
  int i=0;

  cout<<endl;
  
  while(game==false){


      row=0;
      column=0;
      countColumn=0;
      i=0;
      file.open(boardName.c_str(),ios::in);
      
      if(!file.is_open()){
      
      cerr<<"Check Your file which is containing board name or make sure that you have a file with that name :)";
      cerr<<"\n\nThe program is ending \n\n";
      exit(1);
  }

      while(!(file.eof()) ){
         
           getline(file, board);
           i=0;
           
      while(board[i] == '*' || board[i]==' '){
          
        if(count>=2){
           
 
            if(board[i] == '*'){
           
             multipleObject[check].gameBoard[row][column].setChoose('_');
            
            
           }
           
     
  
           
     }
        column++;
      i++;
   }
          
         row++;
         
          if(countColumn<column)
            countColumn=column;
         
            column=0;
         
            
          

      }
      
 
    if(count<=1)  //BİR DEFA DYNAMİC HAFIZA ALMASINI İCİN SART KOYDUM
      for(int a=1;a<=6;a++){
         multipleObject[a].gameBoard=new Cell*[row];
         for(int i=0;i<row;i++)
            multipleObject[a].gameBoard[i]=new Cell[column];
  
        }
   
      
  count++;
 
  checkRow=row-1;
 
 
 
  multipleObject[1].temp2.setGameMode(gameMode);  // zaten bunu bir tek burda set ettigimden single veya multiple oyun etkilemez
  
  if(gameMode== 'S'){
     row=row-1;
     
      if(count < 3)
          file.close();
      
      if(count>=3){  //sadece 2 defa donmesi icin yaptim
   
       setGame(file,row, countColumn, mode, check);
       game=true;
       playGame(gameMode);
      
      }
      
     
      
  }
  
  if(gameMode == 'M'){
      
       if(count <= 3)
          file.close();
      
      if(count>=4){
      
     row=row-1;
     setGame(file,row, countColumn, mode ,check);
     check++;
             
             
     cout<<"enter board file name = ";
     cin>>boardName;
              
     cout<<"enter Mod = ";
     cin>>mode;
    
     if(check>=5){
       game=true;
       playGame(gameMode);
       
     }
      count =2;
      }       
      
  }
  
  }
  }


int ConnectFour::Cell::setRow(int row1) {

	row = row1;
	return row;
}

char ConnectFour::Cell::setMode(char mode1) {

	mode = mode1;
	return mode;
}

int ConnectFour::Cell::setColumn(int column1) {

	column = column1;
	return column;
}



void ConnectFour::Cell::setChoose(char choosem) {
	choose = choosem;

	
}

char ConnectFour::Cell::setGameMode(char mode2) {
	gameMode = mode2;
	return gameMode;
}

string ConnectFour::Cell::setChooseCheck(string choice) {

	chooseCheck = choice;
	return chooseCheck;
}

int ConnectFour::Cell::setLivingCells(int livingCell) {

	livingCells += livingCell;
	return livingCells;
}

int ConnectFour::play(string cellPosition, string playerMod, int object) {

	//hocam sadece cellPosition kullanÄ±n yazmadÄ±gÄ±ndan iki parametre daha ekledim 
	int control = 0;
	int choose = 0;
	bool playerCh = false;

	char mode = multipleObject[object].temp2.getMode();  //gerekli bilgileri classdan cekiyorum
	int row = multipleObject[object].temp2.getRow();
	int column = multipleObject[object].temp2.getColumn();
	string chooseCheck = multipleObject[object].temp2.getChooseCheck();
	int livingCell = 0;

	while (playerCh == false) {

		control = 0;

		for (int i = 0; i < column; i++) {

			if (cellPosition[1] == '\0') {     //girilen seyin char mÄ± strÄ±ng mÄ± olduguna bakÄ±yorum
				if (cellPosition[0] == chooseCheck[i]) {
					choose = i;
					playerCh = true;
					break;

					
				}

				if (cellPosition[0] != chooseCheck[i])      //eÃ°er eÃŸit deÃ°ilse bu control integer'ÃœnÃœ arttÃœrdÃœm
					control++;

			}

			else if (cellPosition[1] != '\0') {
				oldBoard(cellPosition, object);  //girilen deger string ise load veya save oldugunu kontrol etmesÄ± Ä±cÄ±n oldBoard a gonderdÄ±m
			}


		}
		if (playerCh == true)
			break;


		if (control == column) {     //control bu deÃ°ere eÃŸit olmussa farklÃœ karakterle oynuyor demektir
			cout << "\nPlease just try to play capital letters \n\n\t\t   which is shown upper  >> like capital A <<  = ";
			cin >> cellPosition;
			playerCh = false;         //yeni giriÃŸ yapmasÃœ iÃ§in playerCh' yi false yaptÃœm

		}

		if (control != column && multipleObject[object].gameBoard[0][choose].getChoose() != '_') {
			// dolu bir yere oynarsa eÃ°er bu uyariyi versin diye ayarladim

			cout << "\n\nThe column which you are trying to play is full try another one please = ";
			cin >> cellPosition;
			playerCh = false;         //false yaparak tekrar hamle yapmasÃœ iÃ§in yukari dÃ¶nderdim

		}

		else if (control != column && multipleObject[object].gameBoard[0][choose].getChoose() == '_')
			break;



	}




	for (int i = (row - 1); i >= 0; i--) {  // oynayanÃœn seÃ§tmÄ±s oldugu sÃŒtunu kontrol etmesi iÃ§in for loop oluÃŸturdum

		if (multipleObject[object].gameBoard[i][choose].getChoose() == '_') {
			//en alt satÃœrdan baslayarak kontrol etmesini ve bos yer varsa X koymasÃœnÃœ saÃ°ladÃœm

			if (playerMod == "player1") {
				multipleObject[object].gameBoard[i][choose].setChoose('X');
				livingCell++;
				return 0;

			}

			 if (playerMod == "player2") {
				multipleObject[object].gameBoard[i][choose].setChoose('O');
				livingCell++;
				return 0;
			}
                        
                       
		}
                
                
	} //for un sonu
        
        
                  cout<<" make a legal move = ";
                    cin>>cellPosition;
                    playerCh=false;
                       

	multipleObject[1].temp2.setLivingCells(livingCell); // livingCells sayÄ±sÄ±nÄ± set ettim
	return 0;    // fonkisyonun baÃŸarÃœyla sonlandÃœrÃœlmasÃœnÃœ saÃ°ladÃœm

}

int ConnectFour::play(int object) {



	int row = multipleObject[object].temp2.getRow();
	int column = multipleObject[object].temp2.getColumn();

	int check = 0;
	int z = 0;  // z ve y iÃ§in boyutunu aÃŸmayacak ÃŸekilde random sayÃœ atadÃœm
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
					// 3 tane iÃ§ iÃ§e for kullnarak board'un en asaÃ°ÃœsÃœna ve saÃ°Ãœna gittim
					// ve aÃŸaÃ°Ãœdan yukarÃœ doÃ°ru sÃŒtunlarÃœ kontrol ettim

					if (multipleObject[object].gameBoard[x][j].getChoose() == 'X')
						//eÃ°er X ile karÃŸÃœlasÃœrsa daha Ã¶nceden tanÃœmladÃœÃ°Ãœm integeri arttÃœrdÃœm
						checkMove++;                 // 3 tane ÃŒst ÃŒste X varsa sonucta burasÃœ 3 olacak

					else if (multipleObject[object].gameBoard[x][j].getChoose() != 'X')
						//X gÃ¶rmezse o ana kadar saydÃœÃ°Ãœ deÃ°erleri sÃœfÃœrlÃœyorum
						checkMove = 0;

					if (checkMove <= 3 && x == 0)    // x bulunduÃ°u satÃœr ve eÃ°er x=0 olduÃ°unda checkMOve hala 3 olmamÃœssa
						checkMove = 0;      // bu daha da olamayacaÃ°Ãœ anlamÃœna gelir o yÃŒzden tekrar sÃœfÃœra atadÃœm

					if (multipleObject[object].gameBoard[x][j].getChoose() == 'O')
						// AynÃœ mantÃœkla X deÃ°il O karakterini kontrol ettirdim
						checkMove3++;             // eÃ°er ÃŒst ÃŒste varsa burasÃœ artacak sÃŒrekli

					else if (multipleObject[object].gameBoard[x][j].getChoose() != 'O')
						// eÃ°er O gÃ¶rmezse sÃœfÃœrlÃœyorum ki diÃ°er sÃŒtuna geÃ§tiÃ°inde
						checkMove3 = 0;                 // bÃœraktÃœÃ°Ãœ yerden baÃŸlamasÃœn

					if (checkMove3 <= 3 && x == 0)
						//AynÃœ X de geÃ§erli olduÃ°u gibi satÃœr o a gelidÃ°inde hala 3 olmamÃœssa sÃœfÃœrlÃœyorum
						checkMove3 = 0;

					if ((checkMove == 3 || checkMove3 == 3) && multipleObject[object].gameBoard[x - 1][j].getChoose() == '_') {
						//yukarÃœdaki deÃ°erlerin herhangi biri 3 oldugunda hemen yanÃœ bossa hamle yaptÃœrÃœyorum
						multipleObject[object].gameBoard[x - 1][j].setChoose('O');
						livingCells++;
						multipleObject[1].temp2.setLivingCells(livingCells);
						gameover = true;
						return 0;      // bu if gerÃ§ekleÃŸirse fonksiyondan baÃŸarÃœ ile cÃœkmasÃœnÃœ saÃ°lÃœyorum

					}

				}  // en iÃ§teki for'un sonu



			}  // 2. for'un sonu


			if (gameover == true)
				return 0;  // olurda buraya kadar gelip fonksiyon sonlanmamÃœs olursa diye tekrar return ediyorum

			for (int b = 0; b <= row - 1; b++) { // en dÃœstaki for iÃ§inde bu for loop'u

				if (multipleObject[object].gameBoard[i][b].getChoose() == 'X')
					//bu sefer yanyana olan X leri kontrol ediyorum
					checkMove1++;        //ÃŒsteki mantÃœkla aynÃœ olarak tanÃœmlamÃœs oldugum integer deÃ°erini arttÃœrÃœyorum

				else if (multipleObject[object].gameBoard[i][b].getChoose() != 'X')
					// X gÃ¶rmedÃ°inde sÃœfÃœrlÃœyorum
					checkMove1 = 0;

				if (checkMove1 <= 3 && b == row - 1)  //eÃ°er satÃœrÃœn sonuna gelmiÃŸ ve integer 3 ten kÃŒÃ§ÃŒk deÃ°er
					checkMove1 = 0;      // tutuyorsa tekrar o satÃœrda 3 olamaz sÃœfÃœrlÃœyorum ki sonraki satir etkilenmesin

				if (multipleObject[object].gameBoard[i][b].getChoose() == 'O')   //aynÃœ mantÃœkla O karakterini kontrol ediyorum
					checkMove3++;

				else if (multipleObject[object].gameBoard[i][b].getChoose() != 'O')
					checkMove3 = 0;

				if (checkMove3 <= 3 && b == row - 1)   //aynÃœ mantÃœkla bir sonraki satÃœrÃœ etkilemesin diye sÃœfÃœrlÃœyorum
					checkMove3 = 0;


				if (checkMove1 == 3 || checkMove3 == 3) {  //herhangi biri ÃŒÃ§ oldugunda hamle yapmasÃœ lazÃœm

					if (b + 1 <= row - 1) {        //sonucta 3 oldugundaki b deÃ°erinin bir fazlasÃœna hamle yapmasÃœ lazÃœm
												   //eÃ°er b+1 row dan fazla olursa program hata verir onun Ã¶nÃŒne geÃ§iyorum

						if (i == row - 1 && multipleObject[object].gameBoard[i][b + 1].getChoose() == '_') {

							multipleObject[object].gameBoard[i][b + 1].setChoose('O');
							//  b+1 bossa oraya hamle yaptÃœrÃœyorum
							gameover = true;
							livingCells++;
							multipleObject[1].temp2.setLivingCells(livingCells); //livingCell i set ediyorum
							return 0;       //computerMove fonksiyonundan cÃœkartÃœyorum tekrar hame yapmasÃœn diye

						}

						else if (i != row - 1) {  // i !=row-1 ise hamle yapacagÃœ yerin bir altÃœnÃœ kontrol ettiriyorum

							if (multipleObject[object].gameBoard[i + 1][b + 1].getChoose() != '_' && gameBoard[i][b + 1].getChoose() == '_') {

								gameBoard[i][b + 1].setChoose('O');
								//eÃ°er bir altÃœ boÃŸ deÃ°ilse ve hamle yapacag yer boÃŸ ise yaptÃœrÃœyorum
								gameover = true;
								livingCells++;
								multipleObject[1].temp2.setLivingCells(livingCells);
								return 0;      //hamle yapmÃœssa fonksiyonu sonlandÃœrÃœyorum

							}

						}

					}



					if (b - 3 >= 0) {   // saÃ°Ãœna hamle yapmasÃœna saÃ°lamÃœstÃœm burada ise soluna yaptÃœryorum

						if (i == row - 1 && gameBoard[i][b - 3].getChoose() == '_') {
							// eÃ°er en alt satÃœrda ise yapÃœyor

							multipleObject[object].gameBoard[i][b - 3].setChoose('O');
							//aynÃœ sekilde b-3 ile 3 birim geriye gidip kontrol ettiriyorum
							gameover = true;        //ve bossa hamle yaptÃœrÃœyorum
							livingCells++;
							multipleObject[1].temp2.setLivingCells(livingCells);
							return 0;

						}

						else if (i != row - 1) {
							//en alt satÃœrda deÃ°ilse hamle yapacagÃœ yerin altÃœnÃœ kontrol ettiriyorum

							if (multipleObject[object].gameBoard[i + 1][b - 3].getChoose() != '_' && gameBoard[i][b - 3].getChoose() == '_') {

								multipleObject[object].gameBoard[i][b - 3].setChoose('O');
								//yukarÃœdaki ÃŸartlarÃœ saglÃœyorsa  hamle yaptÃœrÃœyorum
								gameover = true;
								livingCells++;
								multipleObject[1].temp2.setLivingCells(livingCells);
								return 0;  //hamle yapmÃœssa tekrar yapmasÃœnÃœ engelliyorum

							}

						}  //else if in sonu

					}   // b-3 >0 Ãœ kontrol eden if in sonu

					if (multipleObject[object].gameBoard[i][b - 3].getChoose() != '_' || multipleObject[object].gameBoard[i][b + 1].getChoose() != '_')
						break;  //aksi saÃ°lanÃœrsa  for loop undan cÃœkarÃœyorum



				} //checkMove1 integerini kontrol eden if yapÃœsÃœnÃœn sonu


			}  // 4.forun sonu(b nin tanymly oldugu)

			if (gameover == true)
				return 0;   // olurda gameover true olmus ve hala cÃœkmamÃœs olursa diye




		}  // en dÃœstaki for loop 'un sonu



		   //sol taraftan Ã§apraz kontrol
		int i = row - 1;  // bu deÃ°erleri asagÃœdaki yapmasÃœnÃœ istediÃ°im kontrol iÃ§in atadÃœm
		int j = 0;
		int a = 1;

		while (i >= 0) {   //en ÃŒst satÃœra Ã§ÃœktÃœgÃœnda daha da arama yapmamasÃœ iÃ§in o an bÃŒyÃŒk olmalÃœ

			while (j != (row - a)) {   // j yi a kadar azaltÃœp kontrol ettiriyorum ki Ã§apraz olsun

				if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')   // her gÃ¶rdÃŒÃ°ÃŒ x i sayacak
					checkMove2++;

				else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')
					// arka arkaya gelmediÃ°ini anladÃœgÃœnda sÃœfÃœrlayacak
					checkMove2 = 0;

				if (checkMove2 <= 3 && i == 1)
					//3 ten kÃŒÃ§ÃŒk oldugunda ve bastan 1. satÃœr olduÃ°unda artÃœk Ã§apraz bakarsa hata verir
					checkMove2 = 0;
				// board boyutu belli oldugundan dÃœsarÃœ cÃœkar ve hata verir bu yÃŒzden sÃœfÃœrladÃœm ÃŸart saÃ°landÃœÃ°Ãœnda

				if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')
					checkMove3++;         // aynÃœ sekilde O sayÃœsÃœnÃœ kontrol ettirdim

				else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')
					checkMove3 = 0;                // arka arkaya gelmiyorsa sÃœfÃœrladÃœm

				if (checkMove3 <= 3 && i == 1)
					checkMove3 = 0;               //ÃŒsteki sart gibi kontrol ettim boardun dÃœsÃœna cÃœkmamak iÃ§in


				if ((checkMove2 == 3 || checkMove3 == 3) && i - 1 >= 0)
					//herhangi biri 3 oldugunda boardun dÃœsÃœna cÃœkarmadan bir altina ve hamle yapacagÃœ yeri kontrol edip hamle yaptÃœrÃœyorum
					// 

					if (multipleObject[object].gameBoard[i - 1][j + 1].getChoose() == '_' && multipleObject[object].gameBoard[i][j + 1].getChoose() != '_') {
						multipleObject[object].gameBoard[i - 1][j + 1].setChoose('O');

						gameover = true;
						livingCells++;
						multipleObject[1].temp2.setLivingCells(livingCells);
						return 0;    //hamle yaptÃœgÃœnda fonksiyondan cÃœkardÃœm
					}


				i--;   //sol tarafa Ã§apraz ilerlemesini saglamak iÃ§in i'yi azaltÃœp j'yi arttÃœrÃœyorum
				j++;


			}  //iÃ§teki while loop'unun sonu

			if (gameover == true)
				return 0;


			a++;   //a yÃœ her seferinde 1 arttÃœrarak satÃœr sayÃœsÃœnÃœn 0 dan kÃŒÃ§ÃŒk olmadan dÃ¶ngÃŒden cÃœkmasÃœnÃœ sagladÃœm (i< row-a  oldugundan)
			i = row - a;     //bir ÃŒst satrya Ã§ykmasyny sa?ladym ki tekrar Ã§apraz arayabilsin
			j = 0;        //j yi sÃœfÃœrladÃœm ki bir ÃŒst satÃœra cÃœktÃœgÃœnda en sagdan  yani boyut(row) kac ise oradan baslasÃœn kontrol etmeye



		}    //soldan Ã§apraz kontrol sonu



		i = row - 1;   // deÃ°erleri tekrar dÃŒzenleyip aÃŸaÃ°Ãœdaki loop iÃ§in gerekli ÃŸartlarÃœ olusturuyorum
		a = 1;
		j = row - 1;



		//saÃ° taraftan Ã§apraz kontrol baÃŸlangÃœcÃœ

		while (i >= 3) {   // i=3 oldugunda daha 3 tane Ã§apraz gelse bile hamle yapacak yer olmadÃœgÃœnda >=sartÃœ koydum
						   // >= cÃŒnkÃŒ o ana kadar geip 3 oldugunda 4  e bakmaz

			while (j >= a) {    // j yi Ã§apraz gidebilmesi iÃ§in her seferÃŸnde a dan bÃŒyÃŒk olarak ayarlÃœyorum


				if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')
					//arka arkaya bu geliyor mu anlamak iÃ§in yazdym
					checkMove2++;


				else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')
					//e?er arka arkaya ayny sey gelirken birden bu gelirse syfyrlasyn diye olusturdum
					checkMove2 = 0;


				if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')
					checkMove3++;


				else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')
					checkMove3 = 0;


				if (checkMove2 == 3 || checkMove3 == 3) {

					if (i - 1 >= 0)
						if (multipleObject[object].gameBoard[i - 1][j - 1].getChoose() == '_'&& multipleObject[object].gameBoard[i][j - 1].getChoose() != '_') {

							multipleObject[object].gameBoard[i - 1][j - 1].setChoose('O');
							gameover = true;
							livingCells++;
							multipleObject[1].temp2.setLivingCells(livingCells);
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



		   //  en altta 0 ve row-1 arasynda kalan sa? caprazlary degerlendyrmek iÃ§in

		i = row - 1;  //deÃ°erleri tekrar aÃŸaÃ°Ãœdaki loop iÃ§in ayarlÃœyorum
		j = 1;
		a = 1;

		while (j != row && (row - a) >= 3) {
			//j boyuta eÃŸit deÃ°ilse ve 3 den fazla yer fazla ÃŒstte kontrol ettiriyorum ki dÃœsarÃœ cÃœkmasÃœn

			while (j <= (row - 1)) {    // j'yi bu ifadeden kÃŒÃ§ÃŒk tutarak size iÃ§erisinde tutuyorum

				if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')
					//aynÃœ ÃŒstekiler gibi ve burada Ã§aprazlarÃœ kontrol ettiriyorum
					checkMove1++;

				else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')
					checkMove1 = 0;

				if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')
					checkMove2++;

				else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')
					checkMove2 = 0;


				if (checkMove1 == 3 || checkMove2 == 3) {  // 3 tane Ã§apraz gelirse hamle yaptÃœrÃœyoum

					if (multipleObject[object].gameBoard[i - 1][j + 1].getChoose() == '_' &&  multipleObject[object].gameBoard[i][j + 1].getChoose() != '_') {
						multipleObject[object].gameBoard[i - 1][j + 1].setChoose('O');

						gameover = true;
						livingCells++;
						multipleObject[1].temp2.setLivingCells(livingCells);
						break;
					}

				}


				i--;
				j++;

			}


			i = row - 1;  // i'yi yine en alt satÃœra alÃœyorum
			j = a + 1;   // j'yi a kadar arttÃœrÃœyorum ki saga birer birer kaysÃœn
			a++;    // a'yÃœ bir arttÃœrÃœyorum ki j istenilen deÃ°ere ulassÃœn ve en dÃœstaki dÃ¶ngÃŒ kontrol edilsin diye


		}

		// daha fazla akllÃœ hamle yapmasÃœnÃœ istemedim ki oynayan sÃŒrekli yenilmesin

		// o yÃŒzden eÃ°er yukardaki ÃŸartlar gerÃ§ekleÃŸmezse aÃŸaÃ°Ãœdaki loop ile random bir sekilde bir yere O koymasÃœnÃœ saÃ°ladÃœm


		while (gameover == false) {

			for (int i = row - 1; i >= 0; i--)
				if (multipleObject[object].gameBoard[i][y].getChoose() == '_')
					check1++;



			if (check1 >= 1) {

				if (z == row - 1 && multipleObject[object].gameBoard[z][y].getChoose() == '_') {

					multipleObject[object].gameBoard[z][y].setChoose('O');
					gameover = true;
					livingCells++;
					multipleObject[1].temp2.setLivingCells(livingCells);
					return 0;

				}

				else if (z != row - 1 && multipleObject[object].gameBoard[z][y].getChoose() == '_' && multipleObject[object].gameBoard[z + 1][y].getChoose() != '_') {

					multipleObject[object].gameBoard[z][y].setChoose('O');
					gameover = true;
					livingCells++;
					multipleObject[1].temp2.setLivingCells(livingCells);
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

	}    //fonksiyonun basinda tanÃœmlanan gameover sonu


	return 0;

} //computerMove sonu

int ConnectFour::drawBoard(int object) {

	int row = multipleObject[object].temp2.getRow();

	int column = multipleObject[object].temp2.getColumn();
	string chooseCheck = "ABCDEFGHKLMNOPRSTUVYZ";



	cout << endl << endl;

	for (int i = 0; i < column; i++)
		cout << " " <<chooseCheck[i] << "  ";

	cout << endl << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
                    
			cout << "  " << multipleObject[object].gameBoard[i][j].getChoose() << " ";

		}
		cout << endl << endl;
	}

    
	return 0;
}

int ConnectFour::playGame(char gameMode) {

  
  auto chooseCheck = multipleObject[1].temp2.getChooseCheck(); 
  char check;
  char mode = multipleObject[1].temp2.getMode();
  int checking = 0;      // checkGame 'in return ettiÃ°i deÃ°eri buna atamak iÃ§in olusturdum
  bool gameOver = false;
  string move;
  int object=0;
  ifstream file;
  
  getInputs(file);  //ınputlari alacak fonksiyon
  
  if(gameMode=='S'){
   if (mode == 'C') {         //oynayanÃœn bilgisayarla oynamayÃœ seÃ§mesi halinde Ã§alÃœsacak

    cout << endl << endl;
    drawBoard(1);  //oynayanÃœn oynayacagÃœ yerleri gÃ¶rmesi iÃ§in ekrana yazdÃœrma fonksiyonumu Ã§aÃ°ÃœrdÃœm

    while (gameOver == false) {

     cout << "\nEnter your choose = ";
     cin>> move;
                        
     if(move.length()==0)
       exit(1);
                        
                                       
     play(move, "player1", 1);
     cout << endl << endl;
     checking = checkGame(1);    //oyunu control ettiriyorum
     cout << "LivingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
	
     if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

       cout << endl << endl;        //ÃSTEKÃ DEÃERLER DÃNMÃSSE OYNAYAN KAZANMIS DEMEKETÃR
       drawBoard(1);
       cout << "\n\nthe winner is player1111 \n\n ";

       gameOver = true;


     }

     else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
        drawBoard(1);
	cout << "\n\nthe winner is COMPUTER \n\n "; //BU DURUMDA DA BÃLGÃSAYAR KAZANMIS DEMEKTÃR

	gameOver = true;
	//oyunu bitiriyorum

     }

     if (gameOver == true) {

	exit(1);

      }

      drawBoard(1);     // yeni board u Ã§izdiriyorum

      cout << "\nComputer is thinking " << endl;
      play(1);  //bilgisayar hamlesi alÃœyorum

      checking = checkGame(1);// oyunun bitip bitmediÃ°ini kontrol ediyorum


									//checking deÃ°erine gre kazanan varsa oyunu yine bitiryorum

      if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

	drawBoard(1);
	cout << "\n\nthe winner is player1111 \n\n ";
	gameOver = true;

      }

      else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o

	drawBoard(1);
	cout << "\n\nthe winner is COMPUTER \n\n ";
	gameOver = true;

      }

      if (gameOver == true)
	exit(1);


      drawBoard(1);
      cout << "LivingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
     }    // while loop' sonu


}   // en dÃœstaki if sonu


  if (mode == 'P') {         // oynayanÃœn iki kiÃŸilk oyun secmesi durumunda oyun oynatacak yapÃœ iÃ§in baslangÃœc yaptÃœm

    drawBoard(1);       //oynayacak kiÃŸinin hamle yapabileceÃ°i yerleri gÃ¶rebilmesi iÃ§in ekrana cizdirdim

    while (gameOver == false) {

      cout << "\n\n player1111 please play = ";
      cin >> move;

      play(move, "player1", 1);

      cout << endl;
      drawBoard(1);
      cout << "LivingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
      checking = checkGame(1);    //oyunun bitip bitmedi?ini kontrol ettim


      if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {
        drawBoard(1);
// player1 in yenmesi durumunu kontrol edip programÃœ sonlandÃœrdÃœm  yenmemiÃŸÃŸse bu ypaÃœ iÃ§ine girmeyecek zaten progaram devam edecek
	
	cout << "\n\nthe winner is player1111 \n\n ";

        gameOver = true;
	break;

      }

      else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o

	drawBoard(1);
	cout << "\n\nthe winner is player22222 \n\n ";

	gameOver = true;
	break;

      }



      cout << "\n\n player2 please play = ";
      cin >> move;

      play(move, "player2", 1);
      drawBoard(1);       //yeni boardu Ã§izdirdim
      cout << "LivingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
      checking = checkGame(1);            //oyunun bitip bitmedi?ini tekrar kontrol ettim




     if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

	//yukarÃœdaki ile aynÃœ sekilde oyun kontrolÃŒ
       drawBoard(1);           //yenen nasÃœl yendiÃ°ini gÃ¶rsÃŒn diye ekrana cizdime fonkisyonunu Ã§aÃ°rÃœdÃœm
       cout << "\n\nthe winner is player1111 \n\n ";

       gameOver = true;
       break;

     }

     else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
																											  //oyun bitmiÃŸÃŸse programÃœ sonlandÃœrÃœyorum yine

       drawBoard(1);
       cout << "\n\nthe winner is player22222 \n\n ";

       gameOver = true;
       break;

      }  //else if sonu



   }   //while loop u iÃ§in son

}  
  
  
 }
  
  else if(gameMode == 'M'){
      
  while(gameOver == false){
      
   cout << "\n\nplease choose obje >>>*** Obje must be number that 1 to 5 *** <<< = ";
   cin >> object;
                
              
  
   if (multipleObject[object].temp2.getMode() == 'C') {
      drawBoard(object);
      cout << "\nenter move = ";
      cin >> move;
      play(move, "player1", object);
	
      drawBoard(object);
	
      cout << "livingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
	
      checking = checkGame(object);

      if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

	cout << endl << endl;        //ÃSTEKÃ DEÃERLER DÃNMÃSSE OYNAYAN KAZANMIS DEMEKETÃR
	drawBoard(object);
	cout << "\n\nThe winner for " << object << " is player1111 \n\n ";
       


      }

      else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
	drawBoard(object);
	cout << "\n\nthe winner for obje " << object << " is COMPUTER \n\n ";
	//BU DURUMDA DA BÃLGÃSAYAR KAZANMIS DEMEKTÃR



      }
 

      cout << "\nComputer is thinking " << endl;
      play(object);
      checking = checkGame(object);

      drawBoard(object);
      cout << "livingCells = " << temp2.getLivingCells() << endl;

   }



   if (multipleObject[object].temp2.getMode() == 'P') {

     drawBoard(object);
			
     cout << "\nPlayer1 enter your move = ";
     cin >> move;

     play(move, "player1", object);

     checking = checkGame(object);
     drawBoard(object);
      
     cout << "livingCells = " << temp2.getLivingCells() << endl;
     cout << "\nPlayer2 enter your move = ";
     cin >> move;

     play(move, "player2", object);
     checking = checkGame(object);
     
     drawBoard(object);
			
     cout << "livingCells = " << temp2.getLivingCells() << endl;
		
   }

    
   if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

      cout << endl << endl;        //ÃSTEKÃ DEÃERLER DÃNMÃSSE OYNAYAN KAZANMIS DEMEKETÃR
      drawBoard(object);
      cout << "\n\nThe winner for " << object << " is player1111 \n\n ";
    

    }

    else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o

      drawBoard(object);
      cout << "\n\nthe winner for obje " << object << " is COMPUTER \n\n "; //BU DURUMDA DA BÃLGÃSAYAR KAZANMIS DEMEKTÃR

																				//oyunu bitiriyorum

    }



 }
   
 }

  return 0;
  
}

int ConnectFour::checkGame(int object) {
	int row = multipleObject[object].temp2.getRow();

	int column = multipleObject[object].temp2.getColumn();

	int check[12] = { 0 };
	int i = row - 1;
	int a = 1;
	int j = 0;
	int control = 0;
	int gameOver = 0;
	int gameOver1 = 0;
	int d = row - 1;

	//dikey  ve yanlamasÃœna kontrol

	for (int i = (row - 1); i >= 0; i--) {

		for (int j = (column - 1); j >= 0; j--) {

			for (int x = 0; x <= row - 1; x++) {   //computerMOve da oldugu gibi en alt satÃœr ve stundan yukarÃœ dogru kontrol ediyoum

				if ((multipleObject[object].gameBoard[x][j].getChoose() == 'X'))     // X gÃ¶rdÃŒÃ°ÃŒm yerde daha Ã¶nceden tanÃœmladÃœÃ°Ãœm dizinin birinci elemanÃœnÃœ arttÃœrÃœyorum
					check[0]++;

				if (multipleObject[object].gameBoard[x][j].getChoose() != 'X')     //X gÃ¶rmediÃ°i zaman 0 lanÃœyor
					check[0] = 0;

				if (multipleObject[object].gameBoard[x][j].getChoose() == 'O')       //aynÃœ sekilde O karakteri iÃ§inde kontrol ediyorum
					check[1]++;

				else if (multipleObject[object].gameBoard[x][j].getChoose() != 'O')    // O karkaterini gÃ¶rmediÃ°i zaman sÃœfÃœrlanÃœyor
					check[1] = 0;

				if (check[0] == 4) {  // eÃ°er 4 olmussa dikey X'ler doÃ°rultuda arka araya demektir oyunu bitirmek
									  //iÃ§in gerekli komutlarÃœ veriyorum

					for (int c = 0; c <= 3; c++)
						multipleObject[object].gameBoard[x - c][j].setChoose('x');        // en alt satÃœrdan ÃŒste doÃ°ru okudugumdan 4 oldugu andaki x deÃ°erinden c cÃœkartarak
																						  //4 defa ilerleyip hepsini kÃŒÃ§ÃŒk x ile deÃ°iÃŸtiriyorum
					gameOver = 1;    //oyunu kimin bitridÃ°ini connectFour fonksiyonununda denetlemek iÃ§in X yenerse tek, O yenerse Ã§ift
					break;         //olacak ÃŸekilde ayarlÃœyorum

				}

				if (check[1] == 4) {

					for (int c = 0; c <= 3; c++)
						multipleObject[object].gameBoard[x - c][j].setChoose('o');

					gameOver = 2;    //check[1] 4 olursa bilgisayar kazanmÃœs demektir
					break;

				}



			}  // en iÃ§teki for un sonu



			if (gameOver == 1 || gameOver == 2)   // ilk for iÃ§indeki kÃœsÃœm saglanÃœrsa artÃœk geriye kalanlarÃœ kontrol etmeden burdan dÃœsarÃœ aldÃœm
				break;

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')     // bu sefer satÃœr ÃŒzerinde yanyana X var mÃœ kontrol ediyorum
				check[2]++;

			if ((check[2] <= 3 && j == 0))   //j =0 oldugunda ve check[2]<=3 oldugunda artÃœk 4 tane yanyana gelemeyiceÃ°inden check[2] yi sÃœfÃœladÃœm
				check[2] = 0;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')   // X gÃ¶rmediÃ°i zaman sÃœfÃœrladÃœm
				check[2] = 0;

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')     // O gÃ¶rdÃŒÃ°ÃŒnden olusturdugum dizinin 4. elemanÃœnÃœ arttÃœrdÃœm
				check[3]++;

			if ((check[3] <= 3 && j == 0))      //ÃŒste yazdÃœgÃœm gibi bu sart saglanÃœdgÃœnda daha 4 olma ihtimali yoktur
				check[3] = 0;                       //program tekrar tekrar kontrol ettiÃ°inde hep alt satÃœrdan baslayacak alt satÃœrdan
													//ÃŒst satÃœra aynÃœ deÃ°erle giderse ÃŒst satÃœrda 4 tane gelmeden oyunu bitirir
													// o yÃŒzden sÃœfÃœrladÃœm


			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')  //O gÃ¶rmezse sÃœfÃœrlanacak
				check[3] = 0;

			if (check[2] == 4) {          // eÃ°er bu sart sagllanÃœyorsa ilgili yerleri kÃŒÃ§ÃŒk x ile deÃ°istirmeyi sagladÃœÃ¶

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i][j + b].setChoose('x');


				gameOver = 3;          // X kazandaÃœgÃœnda tek sayÃœya atamasÃœnÃœ yapÃœyorum
				break;   // loop tan cÃœkarÃœyorum sart saglanÃœrsa

			}

			if (check[3] == 4) {         //aynÃœ sekilde bu sefer O kazandÃœgÃœnda nasÃœl kazandÃœÃ°ÃœnÃœ gÃ¶stermek iÃ§in kÃŒÃ§ÃŒk o ile deÃ°isiyorum

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i][j + b].setChoose('o');

				gameOver = 4;
				break;              // O kazandÃœÃ°Ãœndan Ã§ift sayÃœya return edip oyunu sonlandÃœrÃœyorum

			}



		}

		if (gameOver == 1 || gameOver == 2)    // yukardaki sartlar saglandÃœgÃœnda fonksiyondan tamamen cÃœkmasÃœnÃœ saglÃœyorum
			break;

		if (gameOver == 3 || gameOver == 4)   //sondaki dÃ¶ngÃŒnÃŒn tekrarlanmasÃœnÃœn Ã¶nÃŒne geciyorum yani
			break;

	}  // en dÃœÃŸtaki for iÃ§in son



	   //sol taraftan Ã§apraz kontrol


	while (i >= 2) {   //2*2 ye geldÃ°inde capraz arasada 4 olmaz o yÃŒzden bu sartÃœ koydum 2 ye esit olma sebibi 2 ye gelene
					   //kadar 2 olmussa 4 olma ihtimalini korumak iÃ§in

		while (j != (row - a + 1)) {   //bu sartÃœ koyarak capraz kontrol ederken saÃ°a dogru sÃŒtun ÃŒzerinden gitme miktarÃœnÃœ ayarladÃœm
			if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')   //arka arkaya bu geliyor mu anlamak iÃ§in yazdÃœm
				check[4]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')    //arka arkaya gelmiyorsa sÃœfÃœrladÃœm
				check[4] = 0;

			if (i == 2 && j <= 2 && check[4] <= 3) //2*2 boyutuna kadar dÃŒstgÃŒnde check hala 4 olmamÃœssa daha olamyÃœcagÃœndan bÃ¶yle yaptÃœm
				check[4] = 0;

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')      //O iÃ§in kontrol ettim
				check[5]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')      // arka arkaya gelmiyorsa sÃœfÃœrladÃœm
				check[5] = 0;

			if (i == 2 && j <= 2 && check[5] <= 3)
				check[5] = 0;
			if (check[4] == 4) {          // olurda 4 tane X Ã§apraz gelmiÃŸse gelen yerleri kÃŒÃ§ÃŒk x yaptÃœm

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i + b][j - b].setChoose('x');

				gameOver = 3;            //gameOver a tek sayÃœ atadÃœm
				break;        //dÃ¶ngÃŒden cÃœkardÃœm

			}

			if (check[5] == 4) {    //eÃ°er 4 tane O gelmiÃŸsse gelen yerleri kÃŒÃ§ÃŒk o ile deÃ°iÃŸtirdim

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i + b][j - b].setChoose('o');

				gameOver = 4;
				break;

			}

			i--;   //sol tarafta en asagÃœdan baslayÃœp Ã§apraz bakmasÃœ iÃ§in i'yi azaltÃœp j'yi arttÃœrdÃœm
			j++;


		}

		a++;   //a yÃœ her seferinde 1 arttÃœrarak satÃœr sayÃœsÃœnÃœn 0 dan kÃŒÃ§ÃŒk olmadan dÃ¶ngÃŒden cÃœkmasÃœnÃœ sagladÃœm( i< row-a  oldugundan)
		i = row - a;  //bir ÃŒst satÃœra Ã§ÃœkmasÃœnÃœ saÃ°ladÃœm  ki tekrar Ã§apraz arayabilsin
		j = 0;           //j yi sÃœfÃœrladÃœm ki bir ÃŒst satÃœra cÃœktÃœgÃœnda en sagdan yani boyut kac ise oradan baslasÃœn kontrol etmeye



	}   //sol taraftan capraz kontrol sonu



	i = row - 1;   //  degerleri eski haline dÃ¶nderiyorum ki asagÃœdaki loop dÃŒzgÃŒn calÃœssÃœn
	a = 1;
	j = row - 1;

	int b = 0;    //bir b intger'Ãœ tanÃœmladÃœm


				  //sag taraftan Ã§apraz kontrol

	while (i >3) {   // en ÃŒst satÃœra cÃœktÃœktan sonra artÃœk capraz aramamak iÃ§in

		while (j >= (a - 1)) {   // sonucta 4 tane capraz olabilmesi iÃ§in i=5 den baslÃœyorsa i=1 oldugunda j=5 olmalÃœ o yÃŒzden bu sartÃœ koydum

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')  //arka arkaya bu geliyor mu anlamak iÃ§in yazdÃœm
				check[6]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')     //gelmiyorsa sÃœfÃœrladÃœm
				check[6] = 0;

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')    // arka arkaya O geliyormu diye kontrol ettim
				check[7]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')    // gelmiyorsa ddiye sÃœfÃœrladÃœm
				check[7] = 0;

			if (check[7]< 1 && i <= 3)   // bu sart saglandÃœgÃœnda kontrol etmesine gerek yok cÃŒnkÃŒ 4 tane arka arkaya olamayacak
				check[7] = 0;

			if (check[6] == 4) {      //4 tane X ilen yeri kÃŒÃ§ÃŒk x ile deÃ°iÃŸtiriyorum

				for (int b = 0; b <= 3; b++) {

					multipleObject[object].gameBoard[i + b][j + b].setChoose('x');

				}

				gameOver = 5;   // X geldÃ°i iÃ§in tek sayÃœya atÃœyorum
				break;  // dÃ¶ngÃŒden cÃœkmasÃœnÃœ saglÃœyorum

			}

			if (check[7] == 4) {       // 4 tane O gelmiÃŸÃŸse onlarÃœ kÃŒÃ§ÃŒk o ile deÃ°iÃŸtiriyorum

				for (int b = 0; b <= 3; b++) {

					multipleObject[object].gameBoard[i + b][j + b].setChoose('o');

				}

				gameOver = 6;    //Ã§ift sayÃœya atÃœyorum
				break; //dÃ¶ngÃŒden cÃœkartÃœyorum

			}


			i--;
			j--;


		}

		if (gameOver == 5 || gameOver == 6)
			break;

		a++;
		i = row - a;     //0. satÃœra geldiginde de loop'un devam etmmesi iÃ§in bu degere atadÃœm
		j = row - 1;     // sol Ã§aprazdan en alt satÃœrdan baslayp sÃŒtun sÃŒtun sola kayabilmesi iÃ§in bu ifadeye atadÃœm j'yi



	}  //sag tarfatan Ã§apraz kontrol   sonu



	   //  en altta 0 ve row-1 arasynda kalan sag caprazlarÃœ degerlendirmek iÃ§in

	i = row - 1;  //degerleri asagÃœdaki loop iÃ§in tekrar ayarladÃœm
	j = 1;
	a = 1;

	while (j != row && (row - a) >= 3) {   // j sÃŒtuna esit degilken ve en altta 3 tane gidecek yer kalmamÃœssa bunu yapmalÃœ yoksa hata
										   //yoksa board un dÃœsÃœna cÃœkacagÃœndan hata verir program

		while (j <= (row - 1)) {    //bunu kullanarak boyutu aÃŸmanÃœn Ã¶nÃŒnde gectim

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'X')  //X gÃ¶rÃŒrse arttÃœrmasÃœn iÃ§in olusturdum
				check[8]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')        // arka arkaya gelmezse sÃœfÃœrlasÃœn diye olusturdum tekrar
				check[8] = 0;

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')       // O gelirse diye
				check[9]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')         //arka arkaya gelmezse diye bunu da sÃœfÃœrladÃœm
				check[9] = 0;


			if (check[8] == 4) {  // 4 tane gelirse oyunun bitmesini saglamak iÃ§in gerekli gameOver sayÃœsÃœnÃœ alÃœyorum

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i + b][j - b].setChoose('x'); // 4 olan yerleri kucuk x yapÃœyorum

				gameOver = 7; //X geldigi icin tek sayÃœya atÃœyorum
				break;

			}

			if (check[9] == 4) {  // O gelmisse eÃ°er 4 defa gelen yerleri kucuk yapÃœyorum

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i + b][j - b].setChoose('o');

				gameOver = 8;     //cift degere atÃœyorum
				break;           // loop tan cÃœkarÃœyorum

			}

			i--;   // aradki acÃœgÃœ capraz kontrol edebilmesi icin i'yi azaltÃœp j'yi arttÃœrÃœyorum
			j++;

		}

		if (gameOver == 7 || gameOver == 8)
			break;         //oyun bitmisse looptan cÃœkartÃœyorum

		i = row - 1;  // i yi yine en alt satÃœr alÃœyorum
		j = a + 1;   //j'yi a kadar arttÃœrÃœyorum ki saga birer birer kaysÃœn hep
		a++;    // a'yÃœ bir arttÃœrÃœyorum ki j istenilen degere ulassÃœn ve en dÃœstaki dÃ¶ngÃŒ kontrol edilsin diye


	}   // alt acÃœktaki saÃ° caprazlarÃœ bulan loop'un sonu



	i = row - 1;      // degerleri asagÃœdaki loop u dogru Ã§alÃœstÃœrmak iÃ§in tekrar degistirdim
	j = row - 2;
	a = 3;



	// en altta arada kalan sola dogru capraz kalan aynÃœ hamleleri bulan kontrol loop'u


	while (j >= 2) {   //board'un dÃœsÃœna cÃœkmamasÃœ iÃ§in gerekli kosullarÃœmÃœ loop'larÃœn iÃ§erisinde tanÃœmlÃœyorum

		while (j >= 0 && i >= 0) {    //boyutu asmamak icin bu sartÃœ yazdÃœm

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'X') // 4 tane X yanyana gelme kontrolu
				check[10]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'X')    //gelmemisse sÃœfÃœra atama
				check[10] = 0;

			if (multipleObject[object].gameBoard[i][j].getChoose() == 'O')         //4 tane yanyana O gelme kontrolu
				check[11]++;

			else if (multipleObject[object].gameBoard[i][j].getChoose() != 'O')     //gelmemÃœsse sÃœfÃœra atama
				check[11] = 0;


			if (check[10] == 4) {  //4 tane X gelmiÃŸsse gelen yerleri kÃŒÃ§ÃŒk yaptÃœm ki oynayan gÃ¶rsÃŒn

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i + b][j + b].setChoose('x');

				gameOver = 9;
				break;

			}

			if (check[11] == 4) {  //4 tane O gelmisse onlarÃœ kucuk yaptÃœm ki oynayan gorsun

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameBoard[i + b][j + b].setChoose('o');

				gameOver = 10;
				break;

			}

			i--;
			j--;

		}

		if (gameOver == 9 || gameOver == 10)   //en dÃœstaki sonraki loop tan cÃœkmak iÃ§in(eger sart saglanÃœrsa tabi)
			break;

		i = row - 1;  // i yi yine en alt satÃœr alyyorum
		j = row - a;  //j'yi a kadar azaltÃœyorum ki sola birer birer kaysyn hep

		a++;          // a'yÃœ bir arttÃœrÃœyorum ki j istenilen degere ulassÃœn ve en dÃœstaki dÃ¶ngÃŒ kontrol edilsin diye

	}

	control = 0;

	for (int i = 0; i <= row - 1; i++) {
		if (multipleObject[object].gameBoard[0][i].getChoose() != '_')
			control++;

		else if (multipleObject[object].gameBoard[0][i].getChoose() == '_')
			control = 0;

		if (control == row) {
			cout << "\nThe board is full and no one is winner ...\n\n\n ";
			cout << endl << control << endl;
			exit(1);
		}
	}






	return gameOver;     //gameOver degiskenine dÃ¶nderiyorum ki kimin yendigini daha sonra kontrol edebileyim

}

int ConnectFour::oldBoard(string input, int object) {
    
	char a;
	char check;
	string name;
	int row = multipleObject[object].temp2.getRow();
	int column = multipleObject[object].temp2.getColumn();
	char mode = multipleObject[object].temp2.getMode();
        char gameMode = multipleObject[1].temp2.getGameMode();

	if (input == "SAVE") {     //SAVE GIRILMISSE KULLANICIDAN ISIM ALIP DOSAYAYA YAZDIRACAK KISIM

		cin.ignore();
		ofstream lastGame;
		cout << "Enter txt filename to save... :  ";
		getline(cin, name);      //getline ile txt ismini aldÃÂ±m
		lastGame.open(name.c_str(), ios::out);    //dosyaya yazdirabilmek iÃÂ§in ÃÂ¶nce dosyayi actim

		if (lastGame.fail()) {
			cerr << "Sorry the folder can not creating!!!\n "; //acÃÂ±lmazsa cerr objesine hata yukledim
			cerr << "try again later \n\n";

		}

		if (lastGame.is_open()) { //acilirsa row \n mode\n board olacak sekilde txt icine kaydettim oyunu

			lastGame << object << endl << row << endl << column << endl << mode << endl;


			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {

					lastGame << multipleObject[object].gameBoard[i][j].getChoose() << endl;

				}

			}


			cout << " \nThe board succesfuly saved \n\n You can play anytime you want \n\n ";
			cout << "if you want to continue playing enter any button" << endl;
			cout << " \n if you want to exit now enter ===>> Z = ";
			
			cout << endl << endl;

		}

		lastGame.close();  //txt yi kapattim

		
			playGame(gameMode);

		
		



	}

	if (input == "LOAD") {        //LOAD KOMUTUNU CAGIRIRSA YUKLEYECEGI  OYUN ICIN TXT ISMI ALAN KISIM

		ifstream lastGame;
		cin.ignore();
		cout << "\n Enter the name of txt that you want to open =  ";
		getline(cin, name);

		lastGame.open(name.c_str(), ios::in);  //txt ismini kullanicinin sectigi sekilde ayarlÃÂ±yorum burada

		if (lastGame.is_open()) {

			lastGame >> object >> row >> column >> mode;  //eski oyunun boyutunu ve mode unu cagirip row ve mode u degistiryorum
			multipleObject[object].temp2.setMode(mode);

			multipleObject[object].temp2.setRow(row);
			multipleObject[object].temp2.setColumn(column);

			

			for (int i = 0; i < row; i++)
				for (int j = 0; j < column; j++) {
					lastGame >> a;
					multipleObject[object].gameBoard[i][j].setChoose(a);

				}


		}

		if (lastGame.fail()) { //txt acilmazsa cerr ile hata mesaji veriyorum

			cerr << "\nERROR NOT READING FILE !!! \nCHECK THE FILE THAT YOU IN ";
			cerr << "\nThe game is continuing which is before you enter " << input << endl << endl;
			playGame(gameMode);

		}

		lastGame.close(); //txt yi kapatiyorum
		cout << "\n \nThe board is coming \n ";

		if (object == 1) {
			cout << " you were playing single game \n";
			cout << " \nYour last row = " << row << endl;
			cout << " Your last column = " << column << endl;

			if (mode == 'C')
				cout << "\n\nYou were playing with computer and we were taking your move \n\t\t so lets continue...:) ";

			if (mode == 'P')
				cout << "\n\nYou were playing player to player game and we were taking your move \n so lets continue...:) ";

			playGame(gameMode);


		}

		if (object != 0) {
			cout << " you were playing multiple game which is object " << object << endl;
			cout << " Your last row = " << row << endl;
			cout << " Your last column = " << column << endl;

			if (mode == 'C')
				cout << "\n\nYou were playing with computer and we were taking your move \n\t\t so lets continue...:) ";

			if (mode == 'P')
				cout << "\n\nYou were playing player to player game and we were taking your move \n so lets continue...:) ";

			playGame(gameMode);


		}



	}

	else {
		cout << "if you try load or save game just write LOAD OR SAVE and click enter button \n\t then we will take txt name from you\n\n";

		cout << "\n No operation is defined about " << input << "\nSo you are redirecting before you enter " << input << endl << endl;
		playGame(gameMode);

	}


	return 0;
}

int main() {

	
	cout << "    ________________________________________" << endl << endl;
	cout << "     >>>>  WELCOME TO CONNECT FOUR   <<<< " << "\t  ///// Ahmed Donmez -----" << endl;
	cout << "    ________________________________________" << "\t\t ----- 141024008 /////" << endl << endl;



       ifstream file;
		

       ConnectFour main(file);
       

	

	return 0;         //oyun bittiÃÂinde main baÃÂarÃÂ±yla bitsin diye 0'a return ediyorum
}
