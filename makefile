all:
	as test.asm -o test.o
	ld --oformat binary test.o -o test
	gcc tinyx.c -o tinyx -g -Wall