CFLAGS = -std=c++14 -g -Wall

all: submission

submission: Program4.o Knapsack.o Card.o
	g++ $(CFLAGS) Knapsack.o Card.o Program4.o -o submission

Program4.o: Program4.cpp Knapsack.o Card.o
	g++ -c $(CFLAGS) Program4.cpp -o Program4.o

Knapsack.o: Knapsack.cpp Knapsack.h Card.o
	g++ -c $(CFLAGS) Knapsack.cpp -o Knapsack.o

Card.o: Card.cpp Card.h
	g++ -c $(CFLAGS) Card.cpp -o Card.o

clean:
	rm -vf *.o submission