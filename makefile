all: object compile

object:
	mkdir -p objects
	gcc -g -c main.c source/*.c -Iheaders && mv *.o objects/

compile:
	gcc -o trab3 objects/*.o -lm

run:
	./trab3 exemplo

valgrind:
	valgrind ./trab3 exemplo
clean:
	rm -r trab3 objects