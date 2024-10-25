#Makefile for hw5
#anna andrade
#aandra12
#B4E772

#compiling tags
CC=g++
CFLAGS= -std=c++11 -pedantic -Wall -Wextra

#linking
digraph_analyzer: digraph_analyzer.o digraph_functions.o
	$(CC) -o digraph_analyzer digraph_analyzer.o digraph_functions.o 

#compiling digraph_analyzer /digraph_function execution block
digraph_analyzer.o: digraph_analyzer.cpp digraph_functions.h
	$(CC) $(CFLAGS) -c digraph_analyzer.cpp 

digraph_functions.o: digraph_functions.cpp digraph_functions.h
	$(CC) $(CFLAGS) -c digraph_functions.cpp 

#remove intermediate files and executable called test to start anew
clean:
	rm -f *.o digraph_analyzer