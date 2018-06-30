all:hello

hello:  GTUSet.o GTUMap.o GTUSetBase.o main.o
	g++ GTUSet.o GTUSetBase.o GTUMap.o main.o -o exe


GTUSet.o : GTUSet.cpp 
	g++ -std=c++0x -c GTUSet.cpp 


GTUMap.o : GTUMap.cpp 
	g++ -std=c++0x -c GTUMap.cpp 



GTUSetBase.o: GTUSetBase.cpp 
	g++ -std=c++0x -c GTUSetBase.cpp


main.o: main.cpp 
	g++ -std=c++0x -c main.cpp 


clean:
	rm *.o exe
