CC = g++
CFLAGS = -Wall -g -std=c++11 -o a.out

all: clean build

build: main.o

main: main.o
	$(CC) $(CFLAGS) -o main main.o Brute.o Greedy.o

main.o: main.cpp Brute.o Greedy.o
	$(CC) $(CFLAGS) main.cpp brute.cpp greedy.cpp
 
Brute.o: subsetSumBrute.h
 
Greedy.o: subsetSumGreedy.h

clean:
	$(RM) *.o *.gch a.out
