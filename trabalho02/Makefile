ipc: main.o children.o output.o pipe.o
	gcc $(CFLAGS) -o ipc main.o children.o output.o pipe.o

main.o: main.c children.h output.h pipe.h
	gcc $(CFLAGS) -c main.c

children.o: children.c
	gcc $(CFLAGS) -c children.c

output.o: output.c
	gcc $(CFLAGS) -c output.c

pipe.o: pipe.c
	gcc $(CFLAGS) -c pipe.c
clean:
	rm -f *.o ipc
