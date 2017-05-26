exe: libseno.so main.o
	gcc -o exe main.o -L. -lseno -lm -Wl,-rpath,-Wl,-rpath='${ORIGIN}'

libseno.so: libseno.o
	gcc -shared -fPIC -o libseno.so libseno.o

libseno.o: libseno.c
	gcc -c -fPIC libseno.c

main.o:
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o exe
