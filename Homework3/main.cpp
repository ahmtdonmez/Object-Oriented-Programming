
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;


class ConnectFour {

public:
	ConnectFour();
	ConnectFour(int, int, char);
	ConnectFour(int);
	void setVector(int, int, char, int);
	int play(string,string, int);   //oyuncunun hamlesinin dogrulugunu kontrol edip  board'un içine atayan fonksiyon
	int play(int);         //bilgisayarýn hamle yapmasýný saglayacak olan fonksiyon   
	int drawBoard(int);            //ekrana boardu cidirecek olan fonksiyon
	int playGame();		 //single time icin calısacak fonksiyon
	int checkGame(int);            // olusturdugum board'u kontrol edip oyunun bitip bitmediðinine karar verecek olan fonksiyon
	    
	int oldBoard(string, int); //LOAD ve SAVE komutları geldiginde calısacak fonksiyon
	void setBoard(int);          //oldBoard tarafından cagrılıp yeni boyutu ayarlayacak olan fonksiyon
	void setMultipleObject();      //multiple oyun icin objeleri alıp olusması icin gerekli komutları verecek fonksiyon
	int multipleGame();       //coklu objeler icin oyunları oynatacak fonksiyon





private:
	class Cell {
	public:
		Cell();
		int setRow(int);   
		int setColumn(int);
		char setChoose(char);
		char setMode(char);
		string setChooseCheck(string);
		char  getChoose();
		int getRow();
		int getColumn();
		char getMode();
		string getChooseCheck();
		int setLivingCells(int);
		static int getLivingCells();   

	private:

		int row;
		int column;
		char choose;
		char mode;
		string chooseCheck;
		static int livingCells;

	};


	
	Cell temp2;
	vector<vector<Cell>> gameCells;
	vector<ConnectFour> multipleObject;

};

 int ConnectFour::Cell::livingCells;     //static membera erismek icin dısardan bunu tanimladim

  ConnectFour::ConnectFour() {     //eger 0 parametre ile olusturulursa nesne minimum sartları olusturması icin olusturdum
	temp2.setRow(4);
	temp2.setColumn(4);
	temp2.setChooseCheck("ABCDEFGHIKLMNOPRSTUVYZ");

}

ConnectFour::ConnectFour(int row, int column, char mode) {

	ConnectFour temp;          //bu constructor single time play icin gerekli sartları hazırlayacak


	for (int i = 1; i <= 2; i++) {
		multipleObject.push_back(temp);    // daha onceden tanımladıgım vektoru bir iki boyutlu tanımlıyorum  

	}

	for (int i = 0; i < row; i++) {
		vector<Cell>temp;
		for (int j = 0; j < column; j++) {
			temp.push_back(temp2);         //gameCells vektorunu olusturuyorum


		}
		gameCells.push_back(temp);
	}


	setVector(row, column, mode, 1);     //gameCells i ayarlayıp set edecek fonksiyonumu cagiriyorum



}

ConnectFour::ConnectFour(int choice) {  //multiple oyun oynanacagı zaman cagrilacak fonksiyon

	ConnectFour temp3;

	for (int i = 0; i <= 5; i++) {
		multipleObject.push_back(temp3);  //odevde istendigi gibi COnnectFour un 5 objesini olusturuyorum

	}


	for (int i = 0; i < 20; i++) {   //Alfabedeki sesli harfleri cıkartarak 20 boyutlu olmasını sagladım
		vector<Cell>temp;
		for (int j = 0; j < 20; j++) {
			temp.push_back(temp2);

		}

		gameCells.push_back(temp);

	}


	setMultipleObject();

}

ConnectFour::Cell::Cell() {
 //bile bile bos bıraktım cunku bisey yapmasını istemiyorum

}

void ConnectFour::setBoard(int object) {
	//oldboard tarafýndan cagrilip yeni boardu ayarlayacak fonksiyon
      
	int row = multipleObject[object].temp2.getRow();  //row ve sutunu objeye göre ayarlıyorum
	int column= multipleObject[object].temp2.getColumn();


	for (int i = 0; i < row; i++) {
		multipleObject[object].gameCells.resize(column);    //oyunu yeni row ve sutuna gore resize ediyorum
		for (int j = 0; j < column; j++)
			multipleObject[object].gameCells[i].resize(row);
	}

	
	for (int i = 0; i < row; i++) {
		vector<Cell>temp;  
		for (int j = 0; j < column; j++) {
			temp.push_back(temp2);   //gameCells i yeni boyuta göre ayarlıyorum


		}
		gameCells.push_back(temp);
	}






}

void ConnectFour::setVector(int row, int column, char mode, int object) {

	multipleObject[object].temp2.setRow(row);  //objeye gelen degiskenlerimi atıyorum
	multipleObject[object].temp2.setColumn(column);
	multipleObject[object].temp2.setMode(mode);

	multipleObject[object].temp2.setChoose('_');
	multipleObject[object].temp2.setChooseCheck("ABCDEFGHIKLMNOPRSTUVYZ");
	multipleObject[1].temp2.setLivingCells(0);

	for (int i = 0; i < row; i++) {
		vector<Cell>temp;
		for (int j = 0; j < column; j++) {
			temp.push_back(temp2);

		}

		multipleObject[object].gameCells.push_back(temp); //gameCells i her bir objeye push_back ediyorum
	}


	for (int i = 0; i < row; i++)      //boardu düzgün gözükmesi icin boardaki heryere _ karakterini atıyorum
		for (int j = 0; j < column; j++)
			multipleObject[object].gameCells[i][j].setChoose('_');


}

void ConnectFour::setMultipleObject() {
 //coklu objeler ıcın gerekli  bilgileri alıp setVectorune tek tek gonderip her objeyi tanımlamıs oluyorum
	int row;
	int column;
	char mode;


	for (int i = 1; i <= (multipleObject.size() - 1); i++) {    //tüm objeleri declare ettim

		cout << "\n\n  Enter information of obje " << i;
		cout << "\n\tEnter row = ";
		cin >> row;

		cout << "\n\tEnter column = ";
		cin >> column;



		cout << "\n\tEnter mode (pvp or pcp) = ";
		cin >> mode;


		setVector(row, column, mode, i);

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

char ConnectFour::Cell::setChoose(char choosem) {
	choose = choosem;

	return choose;

}

string ConnectFour::Cell::setChooseCheck(string choice) {

	chooseCheck = choice;
	return chooseCheck;
}

int ConnectFour::Cell::setLivingCells(int livingCell) {
	
	livingCells += livingCell;
	return livingCells;
}

int ConnectFour::Cell::getRow() {

	return row;
}

int ConnectFour::Cell::getColumn() {

	return column;
}

char ConnectFour::Cell::getChoose() {

	return choose;
}

string ConnectFour::Cell::getChooseCheck() {

	return chooseCheck;
}

char ConnectFour::Cell::getMode() {

	return mode;
}

int ConnectFour::Cell::getLivingCells() {

	
	return livingCells;
}

int ConnectFour::play(string cellPosition,string playerMod, int object) {

//hocam sadece cellPosition kullanın yazmadıgından iki parametre daha ekledim 
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

	   if (cellPosition[1] == '\0') {     //girilen seyin char mı strıng mı olduguna bakıyorum
		if (cellPosition[0] == chooseCheck[i]) {    
			choose = i;
			playerCh = true;
			break;

			cout << "\nchoose = " << choose << endl;
		}

		if (cellPosition[0] != chooseCheck[i])      //eðer eþit deðilse bu control integer'ýný arttýrdým
					control++;

	    }

	   else if (cellPosition[1] != '\0') {
		oldBoard(cellPosition, object);  //girilen deger string ise load veya save oldugunu kontrol etmesı ıcın oldBoard a gonderdım
	   }


	}
	     if (playerCh == true)
			break;


		if (control == column) {     //control bu deðere eþit olmussa farklý karakterle oynuyor demektir
			cout << "\nPlease just try to play capital letters \n\n\t\t   which is shown upper  >> like capital A <<  = ";
			cin >> cellPosition;
			playerCh = false;         //yeni giriþ yapmasý için playerCh' yi false yaptým

		}

		if (control != column && multipleObject[object].gameCells[0][choose].getChoose() != '_') {   
       // dolu bir yere oynarsa eðer bu uyariyi versin diye ayarladim

			cout << "\n\nThe column which you are trying to play is full try another one please = ";
			cin >> cellPosition;
			playerCh = false;         //false yaparak tekrar hamle yapmasý için yukari dönderdim

		}

		else if (control != column && multipleObject[object].gameCells[0][choose].getChoose() == '_')
			break;



	}


	

	for (int i = (row - 1); i >= 0; i--) {  // oynayanýn seçtmıs oldugu sütunu kontrol etmesi için for loop oluþturdum

		if (multipleObject[object].gameCells[i][choose].getChoose() == '_') {    
 //en alt satýrdan baslayarak kontrol etmesini ve bos yer varsa X koymasýný saðladým

			if (playerMod == "player1") {
				multipleObject[object].gameCells[i][choose].setChoose('X');
				livingCell++;
				break;

			}

			else if (playerMod == "player2") {
				multipleObject[object].gameCells[i][choose].setChoose('O');
				livingCell++;
				break;
			}

		}
	} //for un sonu

	multipleObject[1].temp2.setLivingCells(livingCell); // livingCells sayısını set ettim
	return 0;    // fonkisyonun baþarýyla sonlandýrýlmasýný saðladým

}

int ConnectFour::play(int object) {

	
	
	int row = multipleObject[object].temp2.getRow();
	int column = multipleObject[object].temp2.getColumn();

	int check = 0;
	int z = 0;  // z ve y için boyutunu aþmayacak þekilde random sayý atadým
	int y = 0;
	int check1 = 0;
	int f = 0;
	int checkMove = 0, checkMove1 = 0, checkMove2 = 0, checkMove3 = 0;
	bool gameover = false;
	bool randomVal = false;
	int livingCells = 0;

	while (gameover == false) {
		//oyunun istenilen yere kadar bitmemesi için while loop kullandým

		srand(time(NULL));
		for (int i = (row - 1); i >= 0; i--) {

			for (int j = column - 1; j >= 0; j--) {

				for (int x = row - 1; x >= 0; x--) { 
                  // 3 tane iç içe for kullnarak board'un en asaðýsýna ve saðýna gittim
                      // ve aþaðýdan yukarý doðru sütunlarý kontrol ettim

					if (multipleObject[object].gameCells[x][j].getChoose() == 'X')      
                                                 //eðer X ile karþýlasýrsa daha önceden tanýmladýðým integeri arttýrdým
						checkMove++;                 // 3 tane üst üste X varsa sonucta burasý 3 olacak

					else if (multipleObject[object].gameCells[x][j].getChoose() != 'X')     
                                                     //X görmezse o ana kadar saydýðý deðerleri sýfýrlýyorum
						checkMove = 0;

					if (checkMove <= 3 && x == 0)    // x bulunduðu satýr ve eðer x=0 olduðunda checkMOve hala 3 olmamýssa
						checkMove = 0;      // bu daha da olamayacaðý anlamýna gelir o yüzden tekrar sýfýra atadým

					if (multipleObject[object].gameCells[x][j].getChoose() == 'O')          
                                                                // Ayný mantýkla X deðil O karakterini kontrol ettirdim
						checkMove3++;             // eðer üst üste varsa burasý artacak sürekli

					else if (multipleObject[object].gameCells[x][j].getChoose() != 'O')       
                                                         // eðer O görmezse sýfýrlýyorum ki diðer sütuna geçtiðinde
						checkMove3 = 0;                 // býraktýðý yerden baþlamasýn

					if (checkMove3 <= 3 && x == 0)     
                                              //Ayný X de geçerli olduðu gibi satýr o a gelidðinde hala 3 olmamýssa sýfýrlýyorum
						checkMove3 = 0;

					if ((checkMove == 3 || checkMove3 == 3) && multipleObject[object].gameCells[x - 1][j].getChoose() == '_') {
						//yukarýdaki deðerlerin herhangi biri 3 oldugunda hemen yaný bossa hamle yaptýrýyorum
						multipleObject[object].gameCells[x - 1][j].setChoose('O');
						livingCells++;
						multipleObject[1].temp2.setLivingCells(livingCells);
						gameover = true;
						return 0;      // bu if gerçekleþirse fonksiyondan baþarý ile cýkmasýný saðlýyorum

					}

				}  // en içteki for'un sonu



			}  // 2. for'un sonu


			if (gameover == true)
				return 0;  // olurda buraya kadar gelip fonksiyon sonlanmamýs olursa diye tekrar return ediyorum

			for (int b = 0; b <= row - 1; b++) { // en dýstaki for içinde bu for loop'u

				if (multipleObject[object].gameCells[i][b].getChoose() == 'X')           
                                                    //bu sefer yanyana olan X leri kontrol ediyorum
					checkMove1++;        //üsteki mantýkla ayný olarak tanýmlamýs oldugum integer deðerini arttýrýyorum

				else if (multipleObject[object].gameCells[i][b].getChoose() != 'X')        
                                                     // X görmedðinde sýfýrlýyorum
					checkMove1 = 0;

				if (checkMove1 <= 3 && b == row - 1)  //eðer satýrýn sonuna gelmiþ ve integer 3 ten küçük deðer
					checkMove1 = 0;      // tutuyorsa tekrar o satýrda 3 olamaz sýfýrlýyorum ki sonraki satir etkilenmesin

				if (multipleObject[object].gameCells[i][b].getChoose() == 'O')   //ayný mantýkla O karakterini kontrol ediyorum
					checkMove3++;

				else if (multipleObject[object].gameCells[i][b].getChoose() != 'O')
					checkMove3 = 0;

				if (checkMove3 <= 3 && b == row - 1)   //ayný mantýkla bir sonraki satýrý etkilemesin diye sýfýrlýyorum
					checkMove3 = 0;


				if (checkMove1 == 3 || checkMove3 == 3) {  //herhangi biri üç oldugunda hamle yapmasý lazým

					if (b + 1 <= row - 1) {        //sonucta 3 oldugundaki b deðerinin bir fazlasýna hamle yapmasý lazým
							  //eðer b+1 row dan fazla olursa program hata verir onun önüne geçiyorum

						if (i == row - 1 && multipleObject[object].gameCells[i][b + 1].getChoose() == '_') {

							multipleObject[object].gameCells[i][b + 1].setChoose('O');    
                                                                   //  b+1 bossa oraya hamle yaptýrýyorum
							gameover = true;
							livingCells++;
							multipleObject[1].temp2.setLivingCells(livingCells); //livingCell i set ediyorum
							return 0;       //computerMove fonksiyonundan cýkartýyorum tekrar hame yapmasýn diye

						}

						else if (i != row - 1) {  // i !=row-1 ise hamle yapacagý yerin bir altýný kontrol ettiriyorum

							if (multipleObject[object].gameCells[i + 1][b + 1].getChoose() != '_' && gameCells[i][b + 1].getChoose() == '_') {

								gameCells[i][b + 1].setChoose('O');  
                                                                  //eðer bir altý boþ deðilse ve hamle yapacag yer boþ ise yaptýrýyorum
								gameover = true;
								livingCells++;
								multipleObject[1].temp2.setLivingCells(livingCells);
								return 0;      //hamle yapmýssa fonksiyonu sonlandýrýyorum

							}

						}

					}



					if (b - 3 >= 0) {   // saðýna hamle yapmasýna saðlamýstým burada ise soluna yaptýryorum

						if (i == row - 1 && gameCells[i][b - 3].getChoose() == '_') {    
                                                                   // eðer en alt satýrda ise yapýyor

							multipleObject[object].gameCells[i][b - 3].setChoose('O');  
                                                               //ayný sekilde b-3 ile 3 birim geriye gidip kontrol ettiriyorum
							gameover = true;        //ve bossa hamle yaptýrýyorum
							livingCells++;
							multipleObject[1].temp2.setLivingCells(livingCells);
							return 0;

						}

						else if (i != row - 1) {     
                                                          //en alt satýrda deðilse hamle yapacagý yerin altýný kontrol ettiriyorum

							if (multipleObject[object].gameCells[i + 1][b - 3].getChoose() != '_' && gameCells[i][b - 3].getChoose() == '_') {

								multipleObject[object].gameCells[i][b - 3].setChoose('O');   
                                                                          //yukarýdaki þartlarý saglýyorsa  hamle yaptýrýyorum
								gameover = true;
								livingCells++;
								multipleObject[1].temp2.setLivingCells(livingCells);
								return 0;  //hamle yapmýssa tekrar yapmasýný engelliyorum

							}

						}  //else if in sonu

					}   // b-3 >0 ý kontrol eden if in sonu

					if (multipleObject[object].gameCells[i][b - 3].getChoose() != '_' || gameCells[i][b + 1].getChoose() != '_')
						break;  //aksi saðlanýrsa  for loop undan cýkarýyorum



				} //checkMove1 integerini kontrol eden if yapýsýnýn sonu


			}  // 4.forun sonu(b nin tanymly oldugu)

			if (gameover == true)
				return 0;   // olurda gameover true olmus ve hala cýkmamýs olursa diye




		}  // en dýstaki for loop 'un sonu



		   //sol taraftan çapraz kontrol
		int i = row - 1;  // bu deðerleri asagýdaki yapmasýný istediðim kontrol için atadým
		int j = 0;
		int a = 1;

		while (i >= 0) {   //en üst satýra çýktýgýnda daha da arama yapmamasý için o an büyük olmalý

			while (j != (row - a)) {   // j yi a kadar azaltýp kontrol ettiriyorum ki çapraz olsun

				if (multipleObject[object].gameCells[i][j].getChoose() == 'X')   // her gördüðü x i sayacak
					checkMove2++;

				else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')    
                                             // arka arkaya gelmediðini anladýgýnda sýfýrlayacak
					checkMove2 = 0;

				if (checkMove2 <= 3 && i == 1)    
                        //3 ten küçük oldugunda ve bastan 1. satýr olduðunda artýk çapraz bakarsa hata verir
					checkMove2 = 0;          
                         // board boyutu belli oldugundan dýsarý cýkar ve hata verir bu yüzden sýfýrladým þart saðlandýðýnda

				if (multipleObject[object].gameCells[i][j].getChoose() == 'O')
					checkMove3++;         // ayný sekilde O sayýsýný kontrol ettirdim

				else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')
					checkMove3 = 0;                // arka arkaya gelmiyorsa sýfýrladým

				if (checkMove3 <= 3 && i == 1)
					checkMove3 = 0;               //üsteki sart gibi kontrol ettim boardun dýsýna cýkmamak için


				if ((checkMove2 == 3 || checkMove3 == 3) && i - 1 >= 0) 
            //herhangi biri 3 oldugunda boardun dýsýna cýkarmadan bir altina ve hamle yapacagý yeri kontrol edip hamle yaptýrýyorum
																		 // 

					if (multipleObject[object].gameCells[i - 1][j + 1].getChoose() == '_' && multipleObject[object].gameCells[i][j + 1].getChoose() != '_') {
						multipleObject[object].gameCells[i - 1][j + 1].setChoose('O');

						gameover = true;
						livingCells++;
						multipleObject[1].temp2.setLivingCells(livingCells);
						return 0;    //hamle yaptýgýnda fonksiyondan cýkardým
					}


				i--;   //sol tarafa çapraz ilerlemesini saglamak için i'yi azaltýp j'yi arttýrýyorum
				j++;


			}  //içteki while loop'unun sonu

			if (gameover == true)
				return 0;


			a++;   //a yý her seferinde 1 arttýrarak satýr sayýsýnýn 0 dan küçük olmadan döngüden cýkmasýný sagladým (i< row-a  oldugundan)
			i = row - a;     //bir üst satrya çykmasyny sa?ladym ki tekrar çapraz arayabilsin
			j = 0;        //j yi sýfýrladým ki bir üst satýra cýktýgýnda en sagdan  yani boyut(row) kac ise oradan baslasýn kontrol etmeye



		}    //soldan çapraz kontrol sonu



		i = row - 1;   // deðerleri tekrar düzenleyip aþaðýdaki loop için gerekli þartlarý olusturuyorum
		a = 1;
		j = row - 1;



		//sað taraftan çapraz kontrol baþlangýcý

		while (i >= 3) {   // i=3 oldugunda daha 3 tane çapraz gelse bile hamle yapacak yer olmadýgýnda >=sartý koydum
						   // >= cünkü o ana kadar geip 3 oldugunda 4  e bakmaz

			while (j >= a) {    // j yi çapraz gidebilmesi için her seferþnde a dan büyük olarak ayarlýyorum


				if (multipleObject[object].gameCells[i][j].getChoose() == 'X')  
                     //arka arkaya bu geliyor mu anlamak için yazdym
					checkMove2++;


				else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')   
                      //e?er arka arkaya ayny sey gelirken birden bu gelirse syfyrlasyn diye olusturdum
					checkMove2 = 0;


				if (multipleObject[object].gameCells[i][j].getChoose() == 'O')
					checkMove3++;


				else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')
					checkMove3 = 0;


				if (checkMove2 == 3 || checkMove3 == 3) {

					if (i - 1 >= 0)
						if (multipleObject[object].gameCells[i - 1][j - 1].getChoose() == '_'&& multipleObject[object].gameCells[i][j - 1].getChoose() != '_') {

						   multipleObject[object].gameCells[i - 1][j - 1].setChoose('O');
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
			i = row - a;    // her seferinde satýrý a kadar azaltarak aþaðýdan yukraý kontrol ettirdim
			j = row - 1;  
                      // çapraz kontrol yapabilmesi için tekrar deðerini ayný yaptým( yukarda a dan büyük ise while salanacagýndan)



		}  // sað tarfatan çapraz kontrol   sonu



		   //  en altta 0 ve row-1 arasynda kalan sa? caprazlary degerlendyrmek için

		i = row - 1;  //deðerleri tekrar aþaðýdaki loop için ayarlýyorum
		j = 1;
		a = 1;

		while (j != row && (row - a) >= 3) {  
               //j boyuta eþit deðilse ve 3 den fazla yer fazla üstte kontrol ettiriyorum ki dýsarý cýkmasýn

			while (j <= (row - 1)) {    // j'yi bu ifadeden küçük tutarak size içerisinde tutuyorum

				if (multipleObject[object].gameCells[i][j].getChoose() == 'X')          
                      //ayný üstekiler gibi ve burada çaprazlarý kontrol ettiriyorum
					checkMove1++;

				else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')
					checkMove1 = 0;

				if (multipleObject[object].gameCells[i][j].getChoose() == 'O')
					checkMove2++;

				else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')
					checkMove2 = 0;


				if (checkMove1 == 3 || checkMove2 == 3) {  // 3 tane çapraz gelirse hamle yaptýrýyoum

					if (multipleObject[object].gameCells[i - 1][j + 1].getChoose() == '_' &&  multipleObject[object].gameCells[i][j + 1].getChoose() != '_') {
						multipleObject[object].gameCells[i - 1][j + 1].setChoose('O');

						gameover = true;
						livingCells++;
						multipleObject[1].temp2.setLivingCells(livingCells);
						break;
					}

				}


				i--;
				j++;

			}


			i = row - 1;  // i'yi yine en alt satýra alýyorum
			j = a + 1;   // j'yi a kadar arttýrýyorum ki saga birer birer kaysýn
			a++;    // a'yý bir arttýrýyorum ki j istenilen deðere ulassýn ve en dýstaki döngü kontrol edilsin diye


		}

		// daha fazla akllý hamle yapmasýný istemedim ki oynayan sürekli yenilmesin

		// o yüzden eðer yukardaki þartlar gerçekleþmezse aþaðýdaki loop ile random bir sekilde bir yere O koymasýný saðladým


		while (gameover == false) {

			for (int i = row - 1; i >= 0; i--)
				if (multipleObject[object].gameCells[i][y].getChoose() == '_')
					check1++;



			if (check1 >= 1) {

				if (z == row - 1 && multipleObject[object].gameCells[z][y].getChoose() == '_') {

					multipleObject[object].gameCells[z][y].setChoose('O');
					gameover = true;
					livingCells++;
					multipleObject[1].temp2.setLivingCells(livingCells);
					return 0;

				}

				else if (z != row - 1 && multipleObject[object].gameCells[z][y].getChoose() == '_' && multipleObject[object].gameCells[z + 1][y].getChoose() != '_') {

					multipleObject[object].gameCells[z][y].setChoose('O');
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

	}    //fonksiyonun basinda tanýmlanan gameover sonu


	return 0;

} //computerMove sonu

int ConnectFour::drawBoard(int object) {

	int row = multipleObject[object].temp2.getRow();

	int column = multipleObject[object].temp2.getColumn();
	string chooseCheck = "ABCDEFGHKLMNOPRSTUVYZ";



	cout << endl << endl;

	for (int i = 0; i < column; i++)
		cout << "   " << chooseCheck[i] << "   ";

	cout << endl << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << "   " << multipleObject[object].gameCells[i][j].getChoose() << "   ";

		}
		cout << endl << endl;
	}


	return 0;
}

int ConnectFour::playGame() {

	
	auto chooseCheck = multipleObject[1].temp2.getChooseCheck();

	char check;
	char mode = multipleObject[1].temp2.getMode();
	int checking = 0;      // checkGame 'in return ettiði deðeri buna atamak için olusturdum
	bool gameOver = false;
	string move;

	if (mode == 'C') {         //oynayanýn bilgisayarla oynamayý seçmesi halinde çalýsacak

		cout << endl << endl;
		drawBoard(1);  //oynayanýn oynayacagý yerleri görmesi için ekrana yazdýrma fonksiyonumu çaðýrdým

		while (gameOver == false) {


			cout << "\nEnter your choose = ";
			cin >> move;

			cout << endl;

			play(move, "player1", 1);
			cout << endl << endl;
			checking = checkGame(1);    //oyunu control ettiriyorum
			cout <<"LivingCells = "<<multipleObject[1].temp2.getLivingCells()<<endl;
			if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

				cout << endl << endl;        //ÜSTEKÝ DEÐERLER DÖNMÜSSE OYNAYAN KAZANMIS DEMEKETÝR
				drawBoard(1);
				cout << "\n\nthe winner is player1111 \n\n ";

				gameOver = true;


			}

			else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
				drawBoard(1);
				cout << "\n\nthe winner is COMPUTER \n\n "; //BU DURUMDA DA BÝLGÝSAYAR KAZANMIS DEMEKTÝR

				gameOver = true;
				//oyunu bitiriyorum

			}

			if (gameOver == true) {

				exit(1);

			}

			drawBoard(1);     // yeni board u çizdiriyorum

			cout << "\nComputer is thinking " << endl;
			play(1);  //bilgisayar hamlesi alýyorum
			
			checking = checkGame(1);// oyunun bitip bitmediðini kontrol ediyorum
			

									//checking deðerine gre kazanan varsa oyunu yine bitiryorum

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



	}   // en dýstaki if sonu


	if (mode == 'P') {         // oynayanýn iki kiþilk oyun secmesi durumunda oyun oynatacak yapý için baslangýc yaptým

		drawBoard(1);       //oynayacak kiþinin hamle yapabileceði yerleri görebilmesi için ekrana cizdirdim

		while (gameOver == false) {


			cout << "\n\n player1111 please play = ";
			cin >> move;

			play(move, "player1", 1);

			cout << endl;
			drawBoard(1);
			cout << "LivingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
			checking = checkGame(1);    //oyunun bitip bitmedi?ini kontrol ettim


			if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

				// player1 in yenmesi durumunu kontrol edip programý sonlandýrdým  yenmemiþþse bu ypaý içine girmeyecek zaten progaram devam edecek
				drawBoard(1);
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
			drawBoard(1);       //yeni boardu çizdirdim
			cout << "LivingCells = " << multipleObject[1].temp2.getLivingCells() << endl;
			checking = checkGame(1);            //oyunun bitip bitmedi?ini tekrar kontrol ettim




			if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

				//yukarýdaki ile ayný sekilde oyun kontrolü
				drawBoard(1);           //yenen nasýl yendiðini görsün diye ekrana cizdime fonkisyonunu çaðrýdým
				cout << "\n\nthe winner is player1111 \n\n ";

				gameOver = true;
				break;

			}

			else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
																											  //oyun bitmiþþse programý sonlandýrýyorum yine

				drawBoard(1);
				cout << "\n\nthe winner is player22222 \n\n ";

				gameOver = true;
				break;

			}  //else if sonu



		}   //while loop u için son


	}   // en dýstaki if için son

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

	//dikey  ve yanlamasýna kontrol

	for (int i = (row - 1); i >= 0; i--) {

		for (int j = (column - 1); j >= 0; j--) {

			for (int x = 0; x <= row - 1; x++) {   //computerMOve da oldugu gibi en alt satýr ve stundan yukarý dogru kontrol ediyoum

				if ((multipleObject[object].gameCells[x][j].getChoose() == 'X'))     // X gördüðüm yerde daha önceden tanýmladýðým dizinin birinci elemanýný arttýrýyorum
					check[0]++;

				if (multipleObject[object].gameCells[x][j].getChoose() != 'X')     //X görmediði zaman 0 lanýyor
					check[0] = 0;

				if (multipleObject[object].gameCells[x][j].getChoose() == 'O')       //ayný sekilde O karakteri içinde kontrol ediyorum
					check[1]++;

				else if (multipleObject[object].gameCells[x][j].getChoose() != 'O')    // O karkaterini görmediði zaman sýfýrlanýyor
					check[1] = 0;

				if (check[0] == 4) {  // eðer 4 olmussa dikey X'ler doðrultuda arka araya demektir oyunu bitirmek
									  //için gerekli komutlarý veriyorum

					for (int c = 0; c <= 3; c++)
						multipleObject[object].gameCells[x - c][j].setChoose('x');        // en alt satýrdan üste doðru okudugumdan 4 oldugu andaki x deðerinden c cýkartarak
																						  //4 defa ilerleyip hepsini küçük x ile deðiþtiriyorum
					gameOver = 1;    //oyunu kimin bitridðini connectFour fonksiyonununda denetlemek için X yenerse tek, O yenerse çift
					break;         //olacak þekilde ayarlýyorum

				}

				if (check[1] == 4) {

					for (int c = 0; c <= 3; c++)
						multipleObject[object].gameCells[x - c][j].setChoose('o');

					gameOver = 2;    //check[1] 4 olursa bilgisayar kazanmýs demektir
					break;

				}



			}  // en içteki for un sonu



			if (gameOver == 1 || gameOver == 2)   // ilk for içindeki kýsým saglanýrsa artýk geriye kalanlarý kontrol etmeden burdan dýsarý aldým
				break;

			if (multipleObject[object].gameCells[i][j].getChoose() == 'X')     // bu sefer satýr üzerinde yanyana X var mý kontrol ediyorum
				check[2]++;

			if ((check[2] <= 3 && j == 0))   //j =0 oldugunda ve check[2]<=3 oldugunda artýk 4 tane yanyana gelemeyiceðinden check[2] yi sýfýladým
				check[2] = 0;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')   // X görmediði zaman sýfýrladým
				check[2] = 0;

			if (multipleObject[object].gameCells[i][j].getChoose() == 'O')     // O gördüðünden olusturdugum dizinin 4. elemanýný arttýrdým
				check[3]++;

			if ((check[3] <= 3 && j == 0))      //üste yazdýgým gibi bu sart saglanýdgýnda daha 4 olma ihtimali yoktur
				check[3] = 0;                       //program tekrar tekrar kontrol ettiðinde hep alt satýrdan baslayacak alt satýrdan
													//üst satýra ayný deðerle giderse üst satýrda 4 tane gelmeden oyunu bitirir
													// o yüzden sýfýrladým


			else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')  //O görmezse sýfýrlanacak
				check[3] = 0;

			if (check[2] == 4) {          // eðer bu sart sagllanýyorsa ilgili yerleri küçük x ile deðistirmeyi sagladýö

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i][j + b].setChoose('x');


				gameOver = 3;          // X kazandaýgýnda tek sayýya atamasýný yapýyorum
				break;   // loop tan cýkarýyorum sart saglanýrsa

			}

			if (check[3] == 4) {         //ayný sekilde bu sefer O kazandýgýnda nasýl kazandýðýný göstermek için küçük o ile deðisiyorum

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i][j + b].setChoose('o');

				gameOver = 4;
				break;              // O kazandýðýndan çift sayýya return edip oyunu sonlandýrýyorum

			}



		}

		if (gameOver == 1 || gameOver == 2)    // yukardaki sartlar saglandýgýnda fonksiyondan tamamen cýkmasýný saglýyorum
			break;

		if (gameOver == 3 || gameOver == 4)   //sondaki döngünün tekrarlanmasýnýn önüne geciyorum yani
			break;

	}  // en dýþtaki for için son



	   //sol taraftan çapraz kontrol


	while (i >= 2) {   //2*2 ye geldðinde capraz arasada 4 olmaz o yüzden bu sartý koydum 2 ye esit olma sebibi 2 ye gelene
					   //kadar 2 olmussa 4 olma ihtimalini korumak için

		while (j != (row - a + 1)) {   //bu sartý koyarak capraz kontrol ederken saða dogru sütun üzerinden gitme miktarýný ayarladým
			if (multipleObject[object].gameCells[i][j].getChoose() == 'X')   //arka arkaya bu geliyor mu anlamak için yazdým
				check[4]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')    //arka arkaya gelmiyorsa sýfýrladým
				check[4] = 0;

			if (i == 2 && j <= 2 && check[4] <= 3) //2*2 boyutuna kadar düstgünde check hala 4 olmamýssa daha olamyýcagýndan böyle yaptým
				check[4] = 0;

			if (multipleObject[object].gameCells[i][j].getChoose() == 'O')      //O için kontrol ettim
				check[5]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')      // arka arkaya gelmiyorsa sýfýrladým
				check[5] = 0;

			if (i == 2 && j <= 2 && check[5] <= 3)
				check[5] = 0;
			if (check[4] == 4) {          // olurda 4 tane X çapraz gelmiþse gelen yerleri küçük x yaptým

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i + b][j - b].setChoose('x');

				gameOver = 3;            //gameOver a tek sayý atadým
				break;        //döngüden cýkardým

			}

			if (check[5] == 4) {    //eðer 4 tane O gelmiþsse gelen yerleri küçük o ile deðiþtirdim

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i + b][j - b].setChoose('o');

				gameOver = 4;
				break;

			}

			i--;   //sol tarafta en asagýdan baslayýp çapraz bakmasý için i'yi azaltýp j'yi arttýrdým
			j++;


		}

		a++;   //a yý her seferinde 1 arttýrarak satýr sayýsýnýn 0 dan küçük olmadan döngüden cýkmasýný sagladým( i< row-a  oldugundan)
		i = row - a;  //bir üst satýra çýkmasýný saðladým  ki tekrar çapraz arayabilsin
		j = 0;           //j yi sýfýrladým ki bir üst satýra cýktýgýnda en sagdan yani boyut kac ise oradan baslasýn kontrol etmeye



	}   //sol taraftan capraz kontrol sonu



	i = row - 1;   //  degerleri eski haline dönderiyorum ki asagýdaki loop düzgün calýssýn
	a = 1;
	j = row - 1;

	int b = 0;    //bir b intger'ý tanýmladým


				  //sag taraftan çapraz kontrol

	while (i >3) {   // en üst satýra cýktýktan sonra artýk capraz aramamak için

		while (j >= (a - 1)) {   // sonucta 4 tane capraz olabilmesi için i=5 den baslýyorsa i=1 oldugunda j=5 olmalý o yüzden bu sartý koydum

			if (multipleObject[object].gameCells[i][j].getChoose() == 'X')  //arka arkaya bu geliyor mu anlamak için yazdým
				check[6]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')     //gelmiyorsa sýfýrladým
				check[6] = 0;

			if (multipleObject[object].gameCells[i][j].getChoose() == 'O')    // arka arkaya O geliyormu diye kontrol ettim
				check[7]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')    // gelmiyorsa ddiye sýfýrladým
				check[7] = 0;

			if (check[7]< 1 && i <= 3)   // bu sart saglandýgýnda kontrol etmesine gerek yok cünkü 4 tane arka arkaya olamayacak
				check[7] = 0;

			if (check[6] == 4) {      //4 tane X ilen yeri küçük x ile deðiþtiriyorum

				for (int b = 0; b <= 3; b++) {

					multipleObject[object].gameCells[i + b][j + b].setChoose('x');

				}

				gameOver = 5;   // X geldði için tek sayýya atýyorum
				break;  // döngüden cýkmasýný saglýyorum

			}

			if (check[7] == 4) {       // 4 tane O gelmiþþse onlarý küçük o ile deðiþtiriyorum

				for (int b = 0; b <= 3; b++) {

					multipleObject[object].gameCells[i + b][j + b].setChoose('o');

				}

				gameOver = 6;    //çift sayýya atýyorum
				break; //döngüden cýkartýyorum

			}


			i--;
			j--;


		}

		if (gameOver == 5 || gameOver == 6)
			break;

		a++;
		i = row - a;     //0. satýra geldiginde de loop'un devam etmmesi için bu degere atadým
		j = row - 1;     // sol çaprazdan en alt satýrdan baslayp sütun sütun sola kayabilmesi için bu ifadeye atadým j'yi



	}  //sag tarfatan çapraz kontrol   sonu



	   //  en altta 0 ve row-1 arasynda kalan sag caprazlarý degerlendirmek için

	i = row - 1;  //degerleri asagýdaki loop için tekrar ayarladým
	j = 1;
	a = 1;

	while (j != row && (row - a) >= 3) {   // j sütuna esit degilken ve en altta 3 tane gidecek yer kalmamýssa bunu yapmalý yoksa hata
										   //yoksa board un dýsýna cýkacagýndan hata verir program

		while (j <= (row - 1)) {    //bunu kullanarak boyutu aþmanýn önünde gectim

			if (multipleObject[object].gameCells[i][j].getChoose() == 'X')  //X görürse arttýrmasýn için olusturdum
				check[8]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')        // arka arkaya gelmezse sýfýrlasýn diye olusturdum tekrar
				check[8] = 0;

			if (multipleObject[object].gameCells[i][j].getChoose() == 'O')       // O gelirse diye
				check[9]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')         //arka arkaya gelmezse diye bunu da sýfýrladým
				check[9] = 0;


			if (check[8] == 4) {  // 4 tane gelirse oyunun bitmesini saglamak için gerekli gameOver sayýsýný alýyorum

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i + b][j - b].setChoose('x'); // 4 olan yerleri kucuk x yapýyorum

				gameOver = 7; //X geldigi icin tek sayýya atýyorum
				break;

			}

			if (check[9] == 4) {  // O gelmisse eðer 4 defa gelen yerleri kucuk yapýyorum

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i + b][j - b].setChoose('o');

				gameOver = 8;     //cift degere atýyorum
				break;           // loop tan cýkarýyorum

			}

			i--;   // aradki acýgý capraz kontrol edebilmesi icin i'yi azaltýp j'yi arttýrýyorum
			j++;

		}

		if (gameOver == 7 || gameOver == 8)
			break;         //oyun bitmisse looptan cýkartýyorum

		i = row - 1;  // i yi yine en alt satýr alýyorum
		j = a + 1;   //j'yi a kadar arttýrýyorum ki saga birer birer kaysýn hep
		a++;    // a'yý bir arttýrýyorum ki j istenilen degere ulassýn ve en dýstaki döngü kontrol edilsin diye


	}   // alt acýktaki sað caprazlarý bulan loop'un sonu



	i = row - 1;      // degerleri asagýdaki loop u dogru çalýstýrmak için tekrar degistirdim
	j = row - 2;
	a = 3;



	// en altta arada kalan sola dogru capraz kalan ayný hamleleri bulan kontrol loop'u


	while (j >= 2) {   //board'un dýsýna cýkmamasý için gerekli kosullarýmý loop'larýn içerisinde tanýmlýyorum

		while (j >= 0 && i >= 0) {    //boyutu asmamak icin bu sartý yazdým

			if (multipleObject[object].gameCells[i][j].getChoose() == 'X') // 4 tane X yanyana gelme kontrolu
				check[10]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'X')    //gelmemisse sýfýra atama
				check[10] = 0;

			if (multipleObject[object].gameCells[i][j].getChoose() == 'O')         //4 tane yanyana O gelme kontrolu
				check[11]++;

			else if (multipleObject[object].gameCells[i][j].getChoose() != 'O')     //gelmemýsse sýfýra atama
				check[11] = 0;


			if (check[10] == 4) {  //4 tane X gelmiþsse gelen yerleri küçük yaptým ki oynayan görsün

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i + b][j + b].setChoose('x');

				gameOver = 9;
				break;

			}

			if (check[11] == 4) {  //4 tane O gelmisse onlarý kucuk yaptým ki oynayan gorsun

				for (int b = 0; b <= 3; b++)
					multipleObject[object].gameCells[i + b][j + b].setChoose('o');

				gameOver = 10;
				break;

			}

			i--;
			j--;

		}

		if (gameOver == 9 || gameOver == 10)   //en dýstaki sonraki loop tan cýkmak için(eger sart saglanýrsa tabi)
			break;

		i = row - 1;  // i yi yine en alt satýr alyyorum
		j = row - a;  //j'yi a kadar azaltýyorum ki sola birer birer kaysyn hep

		a++;          // a'yý bir arttýrýyorum ki j istenilen degere ulassýn ve en dýstaki döngü kontrol edilsin diye

	}

	control = 0;

	for (int i = 0; i <= row - 1; i++) {
		if (multipleObject[object].gameCells[0][i].getChoose() != '_')
			control++;

		else if (multipleObject[object].gameCells[0][i].getChoose() == '_')
			control = 0;

		if (control == row) {
			cout << "\nThe board is full and no one is winner ...\n\n\n ";
			cout << endl << control << endl;
			exit(1);
		}
	}






	return gameOver;     //gameOver degiskenine dönderiyorum ki kimin yendigini daha sonra kontrol edebileyim

}

int ConnectFour::oldBoard(string input, int object) {

	char a;
	char check;
	string name;
	int row = multipleObject[object].temp2.getRow();
	int column = multipleObject[object].temp2.getColumn();
	char mode = multipleObject[object].temp2.getMode();

	if (input == "SAVE") {     //SAVE GIRILMISSE KULLANICIDAN ISIM ALIP DOSAYAYA YAZDIRACAK KISIM

		cin.ignore();
		ofstream lastGame;
		cout << "Enter txt filename to save... :  ";
		getline(cin, name);      //getline ile txt ismini aldÄ±m
		lastGame.open(name.c_str(), ios::out);    //dosyaya yazdirabilmek iÃ§in Ã¶nce dosyayi actim

		if (lastGame.fail()) {
			cerr << "Sorry the folder can not creating!!!\n "; //acÄ±lmazsa cerr objesine hata yukledim
			cerr << "try again later \n\n";

		}

		if (lastGame.is_open()) { //acilirsa row \n mode\n board olacak sekilde txt icine kaydettim oyunu

			lastGame << object << endl << row << endl << column << endl << mode << endl;


			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {

					lastGame << multipleObject[object].gameCells[i][j].getChoose() << endl;

				}

			}


			cout << " \nThe board succesfuly saved \n\n You can play anytime you want \n\n ";
			cout << "if you want to continue playing enter any button" << endl;
			cout << " \n if you want to exit now enter ===>> Z = ";
			cin >> check;
			cout << endl << endl;

		}

		lastGame.close();  //txt yi kapattim

		if (check != 'Z') {    //oyunun devam etmesini saglayacak secim
			playGame();

		}
		if (check == 'Z')      //oyunu bitirecek secim
			exit(1);




	}

	if (input == "LOAD") {        //LOAD KOMUTUNU CAGIRIRSA YUKLEYECEGI  OYUN ICIN TXT ISMI ALAN KISIM

		ifstream lastGame;
		cin.ignore();
		cout << "\n Enter the name of txt that you want to open =  ";
		getline(cin, name);

		lastGame.open(name.c_str(), ios::in);  //txt ismini kullanicinin sectigi sekilde ayarlÄ±yorum burada

		if (lastGame.is_open()) {

			lastGame >> object >> row >> column >> mode;  //eski oyunun boyutunu ve mode unu cagirip row ve mode u degistiryorum
			multipleObject[object].temp2.setMode(mode);
			
			multipleObject[object].temp2.setRow(row);
			multipleObject[object].temp2.setColumn(column);
			
			setBoard(object);   //eski oyun size'i icin boardu ayarlayacak fonksiyonumu cagirdim
			
			for (int i = 0; i < row; i++)
				for (int j = 0; j < column; j++) {
					lastGame >>a;
					multipleObject[object].gameCells[i][j].setChoose(a);

				}


		}

		if (lastGame.fail()) { //txt acilmazsa cerr ile hata mesaji veriyorum

			cerr << "\nERROR NOT READING FILE !!! \nCHECK THE FILE THAT YOU IN ";
			cerr << "\nThe game is continuing which is before you enter " << input << endl << endl;
			playGame();

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

			playGame();


		}

		if (object != 0) {
			cout << " you were playing multiple game which is object " << object << endl;
			cout << " Your last row = " << row << endl;
			cout << " Your last column = " << column << endl;

			if (mode == 'C')
				cout << "\n\nYou were playing with computer and we were taking your move \n\t\t so lets continue...:) ";

			if (mode == 'P')
				cout << "\n\nYou were playing player to player game and we were taking your move \n so lets continue...:) ";

			multipleGame();


		}
		


	}

	else {
		cout << "if you try load or save game just write LOAD OR SAVE and click enter button \n\t then we will take txt name from you\n\n";

		cout << "\n No operation is defined about " << input << "\nSo you are redirecting before you enter " << input << endl << endl;
		playGame();

	}


	return 0;
}

int ConnectFour::multipleGame() {

	int check;
	int a;
	int obje=0;
	int choose;
	int checking = -1;
	bool gameOver = false;
	bool objectCheck = false;
	string move;

	while (gameOver == false) {

	
		

			cout << "\n\nplease choose obje >>>*** Obje must be number that 1 to 5 *** <<< = ";
			cin >> obje;

		
		if (multipleObject[obje].temp2.getMode() == 'C') {
			drawBoard(obje);
			cout << "\nenter move = ";
			cin >> move;

			play(move, "player1", obje);
			drawBoard(obje);
			cout <<"livingCells = "<< multipleObject[1].temp2.getLivingCells()<<endl;
			checking = checkGame(obje);

			if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

				cout << endl << endl;        //ÜSTEKÝ DEÐERLER DÖNMÜSSE OYNAYAN KAZANMIS DEMEKETÝR
				drawBoard(obje);
				cout << "\n\nThe winner for " << obje << " is player1111 \n\n ";
				

			}

			else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
				drawBoard(obje);
				cout << "\n\nthe winner for obje " << obje << " is COMPUTER \n\n "; 
                             //BU DURUMDA DA BÝLGÝSAYAR KAZANMIS DEMEKTÝR
				
				

			}


			cout << "\nComputer is thinking " << endl;
			play(obje);
			checking = checkGame(obje);

			drawBoard(obje);
			cout << "livingCells = " << temp2.getLivingCells() << endl;
		}


		
		if (multipleObject[obje].temp2.getMode() == 'P') {

		drawBoard(obje);
		cout << "\nPlayer1 enter your move = ";
		cin >> move;

		play(move, "player1", obje);

		checking = checkGame(obje);
		drawBoard(obje);
		cout << "livingCells = " << temp2.getLivingCells() << endl;
		cout << "\nPlayer2 enter your move = ";
		cin >> move;

		play(move, "player2", obje);
		checking = checkGame(obje);

		drawBoard(obje);
		cout << "livingCells = " << temp2.getLivingCells() << endl;
		}


		
		if (checking == 1 || checking == 3 || checking == 5 || checking == 7 || checking == 9) {

			cout << endl << endl;        //ÜSTEKÝ DEÐERLER DÖNMÜSSE OYNAYAN KAZANMIS DEMEKETÝR
			drawBoard(obje);
			cout << "\n\nThe winner for " << obje << " is player1111 \n\n ";
			

		}

		else if (checking == 2 || checking == 4 || checking == 6 || checking == 8 || checking == 10) {    //o
			drawBoard(obje);
			cout << "\n\nthe winner for obje " << obje << " is COMPUTER \n\n "; //BU DURUMDA DA BÝLGÝSAYAR KAZANMIS DEMEKTÝR
			
			//oyunu bitiriyorum

		}



	}




	exit(1);
}

int main() {

	int row = 0, column = 0;      //oyun boyutunu atayacaÄÄ±m integer 
	char mode;       // oyunun bilgisayara karÅÄ± mÄ± yoksa iki kiÅilk oyun mu oldugunu tutacak karakter
	char firstMode;
	cout << "    ________________________________________" << endl << endl;
	cout << "     >>>>  WELCOME TO CONNECT FOUR   <<<< " << "\t  ///// Ahmed Donmez -----" << endl;
	cout << "    ________________________________________" << "\t\t ----- 141024008 /////" << endl << endl;




	cout << "\n\n Single time play --->> S " << endl;
	cout << " Multiple games ---->> M = ";
	cin >> firstMode;





	if (firstMode == 'S') {

		cout << endl << endl;
		cout << "Enter the row = ";
		cin >> row;        //kullanÄ±cÄ±dan oyun boyutunu alÄ±yorum

		cout << "Enter the column = ";
		cin >> column;        //kullanÄ±cÄ±dan oyun boyutunu alÄ±yorum

		cout << "\nWhich one you want to play \n\n  Play computer(pvc)---->> C\n  Two person game(pvp) ---->> P =  ";
		cin >> mode;      // kullanÄ±cÄ±dan oyun seÃ§imini alÄ±yorum

		if (mode == 'C' || mode == 'P')
			cout << "\n To load or save game just write LOAD OR SAVE and click enter button \n\t then we will take txt name from you\n\n";

		ConnectFour main(row, column, mode);
		main.playGame();

	}

	if (firstMode == 'M') {
		ConnectFour multiple(2);
		multiple.multipleGame();
	}


	return 0;         //oyun bittiÄinde main baÅarÄ±yla bitsin diye 0'a return ediyorum
}
