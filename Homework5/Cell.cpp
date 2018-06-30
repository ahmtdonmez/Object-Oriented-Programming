
#include<iostream>
#include<string>
#include "Cell.h"

using namespace std;



Cell::Cell() {       //default constructor u olurda deger atamasi olmazsa diye set ediyorum

      row = 5;
      column = 5;
      columnName = "ABCDEFGHIKLMNOPQRSTUVXYZ";
      mode = 'C';
	


}

void Cell::setColumnNames(){

 columnName =  "ABCDEFGHIKLMNOPQRSTUVXYZ";

}

int Cell::setRow(int _row) {   //setterslari birbir ayarliyorum

	row = _row;
	return row;
}

int Cell::setColumn(int _column) {

	column = _column;
	return column;

}

char Cell::setMode(char _mode) {

	mode =_mode;
	return mode;

}

char Cell::setChoose(char _choose) {

	choose = _choose;
	return choose;
}


void Cell::setPlayerTurn(string _playerTurn) { //Oyunun kimde tutan sitring (player1 veya player2 gibi)

	playerTurn = _playerTurn;

}
