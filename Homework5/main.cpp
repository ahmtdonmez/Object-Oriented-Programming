#include <iostream>
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourUndo.h"



int main()
{

	char game;


	cout << "\n\t >----------------------------------------< \n\t\t\t\t\t\t\t\n ";
	cout << "\t   >>>>> Welcome To ConnectFour Game <<<<< \n";
	cout << "\n\t >----------------------------------------<\t >>>> AHMED DONMEZ \n\n \t\t\t\t\t\t\t\t141024008 <<<<\n  ";


	cout << "\n Choose your game Mode ( D , P or U ) = ";
	cin >> game;

        //asagida secime gore gerekli classlarin objesini olusturdum

	if (game == 'D') {
		ConnectFourDiag deneme;  
		deneme.playGame();

	}

	else if (game == 'P') {
		ConnectFourPlus deneme;
		deneme.playGame();

	}

	else if (game == 'U') {
		ConnectFourUndo deneme;
		deneme.playGame();

	}

	

    return 0;
}

