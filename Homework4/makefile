all:hello

hello: main.o
	g++ -std=c++0x main.cpp -o exe

main.o: main.cpp
	g++ -std=c++0x -c main.cpp 

clean:
	rm *.o exe
