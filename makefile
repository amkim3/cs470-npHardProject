CC = g++
CFLAGS = -Wall -g -std=c++11 -o a.out

all: clean build

build: main.o

main: main.o
	$(CC) $(CFLAGS) -o main main.o Brute.o Greedy.o Sat.o Vc.o BaseConversions.o

main.o: main.cpp Brute.o Greedy.o
	$(CC) $(CFLAGS) main.cpp brute.cpp greedy.cpp  3satToSs.cpp mapFromVC.cpp baseConversions.cpp
 
Brute.o: subsetSumBrute.h
 
Greedy.o: subsetSumGreedy.h

Vc.o: mapFromVC.h

Sat.o: 3satToSs.h

BaseConversions.o: baseConversions.h

clean:
	$(RM) *.o *.gch a.out
