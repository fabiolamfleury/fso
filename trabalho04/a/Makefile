exe: libseno.a main.o
	gcc $(CFLAGS) -o exe main.o libseno.a -lm

libseno.a: libseno.c
	gcc $(CFLAGS) -c libseno.c
	ar rc libseno.a libseno.o
	ranlib libseno.a

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o exe
