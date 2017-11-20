test: pipes.o
	gcc -g -o test pipes.o

pipes.o: pipes.c pipes.h
	gcc -c pipes.c

run: test
	./test

clean:
	rm *.o