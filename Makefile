trigo: clean main.c
	mkdir -p bin
	gcc -O3 -Wall -o bin/trigo main.c -Iinclude -Llib lib/libraylib.a -lraylib -lm

clean:
	rm -rf bin/*