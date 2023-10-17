all: item.o lista.o main.o
	gcc item.o lista.o main.o -o lista_programa -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

lista.o:
	gcc -c lista.c -o lista.o

main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o lista_programa

run:
	time ./lista_programa < 3.in > 3.out

rodar: 
	@make -s all
	@make -s run
