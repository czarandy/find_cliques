CC=g++
CFLAGS=-std=c++0x -g -O3
DEPS=find_cliques.h

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all : find_cliques_example find_cliques_large_matrix

find_cliques_example : find_cliques_example.o find_cliques.o
	$(CC) -o find_cliques_example find_cliques_example.o find_cliques.o $(CFLAGS)

find_cliques_large_matrix : find_cliques_large_matrix.o find_cliques.o
	$(CC) -o find_cliques_large_matrix find_cliques_large_matrix.o find_cliques.o $(CFLAGS)

.PHONY : clean
clean:
	rm -f *.o find_cliques_example find_cliques_large_matrix
