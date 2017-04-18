print_vector: q3.o sort.o ordenate.o
	gcc $(CFLAGS) -o print_vector q3.o sort.o ordenate.o

q3.o: q3.c ordenate.h sort.h
	gcc $(CFLAGS) -c q3.c

sort.o: sort.c
	gcc $(CFLAGS) -c sort.c

ordernate.o: ordenate.c
	gcc $(CFLAGS) -c ordenate.c

clean:
		rm -f *.o print_vector
