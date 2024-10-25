#Makefile for hw7
#anna andrade
#aandra12
#B4E772

#compiling tags
CC=g++
CFLAGS= -std=c++11 -pedantic -Wall -Wextra -g

#linking
cTreeTest: CTreeTest.o CTree.o
	$(CC) -o cTreeTest CTreeTest.o CTree.o

tTreeTest: TTreeTest.o 
	$(CC) -o tTreeTest TTreeTest.o  

#compiling cTreeTest
cTreeTest.o: CTreeTest.cpp CTree.h
	$(CC) $(CFLAGS) -c CTreeTest.cpp 

CTree.o: CTree.cpp CTree.h 
	$(CC) $(CFLAGS) -c CTree.cpp

#compiling tTreeTest
tTreeTest.o: TTreeTest.cpp Tree.h
	$(CC) $(CFLAGS) -c TTreeTest.cpp


#remove intermediate files and executable called test to start anew
clean:
	rm -f *.o cTreeTest
	rm -f *.o tTreeTest