# DOUGLAS AFFONSO CLEMENTINO
# GRR20175877

CC     = gcc -std=gnu99

EXECS  = escalona 

# arquivos-objeto
objects = grafo.o escalona.o

all:  $(EXECS)

escalona: escalona.o  grafo.o 
	$(CC) escalona.o  grafo.o -o escalona

escalona.o: escalona.c grafo.h
	$(CC) -c escalona.c

grafo.o: grafo.c grafo.h 
	$(CC) -c grafo.c

clean:
	-rm $(objects)
	-rm *~

purge: clean
	-rm $(EXECS)
