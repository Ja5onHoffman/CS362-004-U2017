#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

int errs = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; } else { printf("**PASS**\n"); }}

void replaceCopperWith(int card, int p, struct gameState *state);
void verifyTopThree(int p, struct gameState *state);
void verifyDiscard(int *tempHand, int p, int *z, struct gameState *state);

int main() {
  struct gameState state;
  struct gameState oldState;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int handPos = -1;
  int currentPlayer = 0;

  // Additional variables from cardEffect
  int temphand[MAX_HAND];// moved above the if statement
  memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length
  int drawntreasure=0;
  int cardDrawn;
  int z = 0;

  printf("\n----- CARD TEST FOUR -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);


  replaceCopperWith(council_room, 0, &state);

  printHand(0, &state);
  printDeck(0, &state);
  printDiscard(0, &state);


  printHand(1, &state);


}
