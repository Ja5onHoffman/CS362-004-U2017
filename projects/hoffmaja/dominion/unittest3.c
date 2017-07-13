#include <stdio.h>
#include <stdlib.h>
#include <interface.h>

/*********
Unit test for fullDeckCount function.
*********/

int main() {

  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int count = 0, supp = 0;
  printf("\n----- UNIT TEST THREE -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  int count = fullDeckCount(0, adventurer, &state);
  printf("Count: %d\n", count);

}
