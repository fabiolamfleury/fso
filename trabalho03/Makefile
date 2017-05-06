CFLAGS=-pthread -g

threads: main.o
	gcc $(CFLAGS) -o threads main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o threads
