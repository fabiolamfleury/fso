quadrilateral_calc: main.o quadrilateral_calcs.o io_functions.o
	gcc $(CFLAGS) -o calculo_quadrilatero main.o quadrilateral_calcs.o io_functions.o

main.o: main.c io_functions.h io_functions.c
	gcc $(CFLAGS) -c main.c

quadrilateral_calcs.o: quadrilateral_calcs.c quadrilateral_calcs.h new_types.h
	gcc $(CFLAGS) -c quadrilateral_calcs.c

io_functions.o: io_functions.c new_types.h
	gcc $(CFLAGS) -c io_functions.c

clean:
	rm -f *.o quadrilateral_calc
