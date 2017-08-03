#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

/*********
Unit test for fullDeckCount function.
*********/

int errs = 0;
int tests = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; tests++; } else { printf("**PASS**\n"); tests++; }}

void addToDiscard(int p, int card, struct gameState *state);

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int count = 0;
  printf("\n----- UNIT TEST THREE: fukkDeckCount() Function -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Default game start: Deck should include 7 Copppers and 3 Estates.\n");
  count = fullDeckCount(0, copper, &state);
  printf("\nCopper count: %d\n", count);
  assert(count == 7);
  count = fullDeckCount(0, estate, &state);
  printf("Estate count: %d\n", fullDeckCount(0, estate, &state));
  assert(count = 3);

  printf("\nAdding two adventurers to hand.\n");
  addCardToHand(0, adventurer, &state);
  addCardToHand(0, adventurer, &state);
  printHand(0, &state);
  printf("Adventurer count should be 2.\n");
  count = fullDeckCount(0, adventurer, &state);
  printf("Adventurer count: %d\n", count);
  assert(count == 2);

  printf("Discarding two Adventurers.\n");
  addToDiscard(0, adventurer, &state);
  addToDiscard(0, adventurer, &state);
  printDiscard(0, &state);
  printf("Adventurer count should still be 2.\n");
  count = fullDeckCount(0, adventurer, &state);
  printf("Adventurer count: %d\n", count);
  assert(count == 2);

  printf("Adding Smithy directly to discard.\n");
  state.discard[0][state.discardCount[0]] = smithy;
  state.discardCount[0]++;
  printDiscard(0, &state);
  printf("Smithy count should be 1.\n");
  count = fullDeckCount(0, smithy, &state);
  assert(count == 1);

  printf("\nAdding Smithy to hand.\n");
  addCardToHand(0, smithy, &state);
  printHand(0, &state);
  printf("Smithy count should now be 2.\n");
  count = fullDeckCount(0, smithy, &state);
  printf("Smithy count: %d\n", count);
  assert(count == 2);

  printf("\n\n\n");
  printf("UNIT TEST 3 - Total failed tests: %d out of %d\n\n", errs, tests);

  return 0;
}

void addToDiscard(int p, int card, struct gameState *state) {
  for (int i = 0; i <= state->handCount[p]; i++) {
    if (state->hand[p][i] == card) {
      state->discard[p][state->discardCount[p]] = card;
    }
  }
  state->handCount[p]-=1;
  state->discardCount[p]+=1;
}
