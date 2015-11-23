
FILE = graph_degree.o graph_free.o graph_input.o \
	   graph_malloc.o graph_rand.o main.o 
CC = gcc

graph: $(FILE)
	$(CC) $(FILE) -O2 -Wall -g -o graph

graph_degree.o : graph_degree.h
graph_free.o : graph_free.h
graph_input.o : graph_input.h
graph_malloc.o : graph_malloc.h
graph_rand.o : graph_rand.h
main.o : graph_degree.h graph_free.h graph_input.h \
		 graph_malloc.h graph_rand.h main.h

.PHONE: clean
clean:
	rm -rf $(FILE) graph
