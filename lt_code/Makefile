all:_main

_main:main.o lt_function.o
	gcc -o _main -I. $^ -lm

lt_code.o:lt_code.cpp
	g++ -c $<
lt_function.o:lt_function.c
	gcc -c $< 
main.o:main.c
	gcc -c $<
clean:
	rm -fr *.o _main
