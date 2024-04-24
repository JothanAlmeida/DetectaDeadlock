CFLAGS=-O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LIBS=-lm -pthread
EXECUTAVEL=main

all: $(EXECUTAVEL)

$(EXECUTAVEL): vector.o string.o thread.o multiplasInstancias.o main.o
	gcc vector.o string.o thread.o multiplasInstancias.o main.o  $(LIBS) -o $(EXECUTAVEL)


multiplasInstancias.o: multiplasInstancias.c
	gcc $(CFLAGS) -c multiplasInstancias.c

string.o: string.c
	gcc $(CFLAGS) -c string.c

thread.o: thread.c
	gcc $(CFLAGS) -c thread.c

vector.o: vector.c
	gcc $(CFLAGS) -c vector.c

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -rf *.o $(EXECUTAVEL)

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) < teste.txt

run: $(EXECUTAVEL)
	./$(EXECUTAVEL) < teste.txt