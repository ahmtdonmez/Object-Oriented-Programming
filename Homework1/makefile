all:hello

hello: main.o hello.o
	g++ main.cpp -o exe

main.o: main.cpp
	g++ -c main.cpp

hello.o: main.o
	g++ main.o
	./a.out

clean:
	rm *.o exe
