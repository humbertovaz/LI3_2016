### Makefile ###

objects = array.o avl.o clientes.o faturacao.o filial.o \
	   		produtos.o 


CFLAGS=-Wall -ansi -pedantic -O2

all:
	make clean
	make produtos
	make array
	make avl
	make clientes
	make faturacao
	make filial
	make leitura

leitura: src/leitura.c array.o avl.o clientes.o faturacao.o filial.o produtos.o 
	gcc src/leitura.c array.o avl.o clientes.o faturacao.o filial.o produtos.o $(CFLAGS) -o gereVendas -lm

clientes: src/clientes.c src/headers/clientes.h
	gcc src/clientes.c -c $(CFLAGS)


produtos: src/produtos.c src/headers/produtos.h
	gcc src/produtos.c -c $(CFLAGS)


array: src/array.c src/headers/array.h
	gcc src/array.c -c $(CFLAGS)


faturacao: src/faturacao.c src/headers/faturacao.h
	gcc src/faturacao.c -c $(CFLAGS)


filial: src/filial.c src/headers/filial.h
	gcc src/filial.c -c $(CFLAGS)


avl: src/avl.c src/headers/avl.h
	gcc src/avl.c -c $(CFLAGS)


.PHONY : clean
clean :
	rm -f gereVendas
	rm -f $(objects)
	rm -f gesval

