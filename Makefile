CFLAGS = -std=c++14 -g -Wall

all: submission

submission: Program3.o Knapsack.o Card.o
	g++ $(CFLAGS) Knapsack.o Card.o Program3.o -o submission

Program3.o: Program3.cpp Knapsack.o Card.o
	g++ -c $(CFLAGS) Program3.cpp -o Program3.o

Knapsack.o: Knapsack.cpp Knapsack.h Card.o
	g++ -c $(CFLAGS) Knapsack.cpp -o Knapsack.o

Card.o: Card.cpp Card.h
	g++ -c $(CFLAGS) Card.cpp -o Card.o

clean:
	rm -vf *.o submission