CFLAGS = -std=c99 -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

# Unit Tests

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

unittest1: unittest1.c dominion.o rngs.o
		gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

# remove -g flag
unittest2: unittest2.c dominion.o rngs.o interface.o
	gcc -g -o unittest2 unittest2.c dominion.o rngs.o interface.o $(CFLAGS)

# remove -g flag
unittest3: unittest3.c dominion.o rngs.o interface.o
		gcc -g -o unittest3 unittest3.c dominion.o rngs.o interface.o $(CFLAGS)

# remove -g flag
unittest4: unittest4.c dominion.o rngs.o interface.o
		gcc -g -o unittest4 unittest4.c dominion.o rngs.o interface.o $(CFLAGS)

# Card Tests

cardtest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -g -o cardtest1 cardtest1.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -g -o cardtest2 cardtest2.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -g -o cardtest3 cardtest3.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -g -o cardtest4 cardtest4.c dominion.o rngs.o interface.o $(CFLAGS)

# Random tests

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o interface.o -g $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o interface.o -g $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o interface.o
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o interface.o -g $(CFLAGS)

player: player.c interface.o
		gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -rf *.o *.dSYM playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe \
	unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out \
	randomtestadventurer randomtestcard1 randomtestcard2
