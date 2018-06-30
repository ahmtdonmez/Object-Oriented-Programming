all:hello

hello: main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourUndo.o
	g++ main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourUndo.o -o exe

main.o: main.cpp
	g++ -std=c++0x -c main.cpp


Cell.o : Cell.cpp
	g++ -std=c++0x -c Cell.cpp

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -std=c++0x -c ConnectFourAbstract.cpp


ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -std=c++0x -c ConnectFourPlus.cpp

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -std=c++0x -c ConnectFourDiag.cpp

ConnectFourUndo: ConnectFourUndo.cpp
	g++ -std=c++0x -c ConnectFourUndo.cpp


 

clean:
	rm *.o exe
