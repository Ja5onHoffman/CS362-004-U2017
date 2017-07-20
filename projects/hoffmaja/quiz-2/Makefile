CFLAGS = -std=c99 -Wall -fpic -coverage -lm

buildquiz2: testme.c
	gcc -g -coverage -o testme testme.c $(CFLAGS)

run: buildquiz2
	./testme

gcov:
	gcov -b testme


clean:
	rm -rf testme *.dSYM *.gcno *.gcda *.gcov
