all: item.o teste.o
	gcc item.o teste.o -o lista_programa -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

# lista.o:
# 	gcc -c lista.c -o lista.o

teste.o:
	gcc -c teste.c -o teste.o
	 
clean:
	rm *.o lista_programa

run:
	./lista_programa

rodar: 
	@make -s clean
	@make -s all
	@make -s run
