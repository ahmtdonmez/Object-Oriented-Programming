#ifndef CELL_H
#define CELL_H

#include<string>
using namespace std;

class Cell {


public:
	Cell();
	
	int setRow(int);
	int setColumn(int);
	char setChoose(char);
	char setMode(char);
	void setColumnNames();
	void setPlayerTurn(string);
	char  getChoose()const { return choose; }   //getterslari inline yaptim
	string getPlayerTurn()const { return playerTurn; }
	int getRow()const { return row; }
	int getColumn()const { return column; }
	char getMode()const { return mode; }
	string getColumnNames()const { return columnName; }


private:

	int row;
	int column;
	char choose;     //board un icerigini tutacak olan bir char tanimladim
	char mode;      //P(PVP) ve C(PVC) yi tutmasi icin tanimladim
        string columnName;  //sutunlari karakter karakter icerecek olan string
	string playerTurn;  //hamle yapanin kim oldugunu tutuyotum boylece X veya O koyacagim
	

};

#endif // CELL_H

