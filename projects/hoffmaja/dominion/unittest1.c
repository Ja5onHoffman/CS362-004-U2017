#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/*********
Unit test for whoseTurn function.
Initialize a game, change the whoseTurn variable on the
game state multiple times and verify that whoseTurn()
returns the correct player.
*********/

int fail = 1;
#undef assert
#define assert(cond) { if (!(cond)) { printf("FAILED TEST\n"); fail--; }}

int main() {
  struct gameState state;
  // Game states with one through five players
  int numPlayers[5] = { 5, 4, 3, 2, 1};
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;

  printf("----- UNIT TEST ONE -----\n");
  int i;
  for (i = 0; i < 5; i++) {
    initializeGame(numPlayers[i], k, seed, &state);
    printf("\nTesting with %d players.\n", numPlayers[i]);
    int currentPlayer = 0; printf("Current player = %d\n", currentPlayer);
    printf("Changing player to %d\n", numPlayers[i]);
    state.whoseTurn = numPlayers[i];
    printf("Current player now %d\n", whoseTurn(&state));
    assert(whoseTurn(&state) == numPlayers[i]);
  }

  printf("\nUNIT TEST 1: %d failed tests.\n", abs(fail-1));
}
