exe: main.o libseno.so
	gcc -o exe main.c -ldl

libseno.so: libseno.o
	gcc -shared -fPIC -o libseno.so libseno.o

libseno.o: libseno.c
	gcc -c -fPIC libseno.c

clean:
	rm -f *.o exe
