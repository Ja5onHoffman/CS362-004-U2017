#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

// Card test for smithy
// 1. Current player should receive exact 3 cards.
//
// 2. 3 cards should come from his own pile.
//
// 3. No state change should occur for other players.
//
// 4. No state change should occur to the victory card piles and kingdom card piles.

int errs = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; } else { printf("**PASS**\n"); }}

void replaceCopperWith(int card, int p, struct gameState *state);
int getHandPos(int p, int card, struct gameState *state);

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int handPos = -1;
  printf("\n----- CARD TEST ONE -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Adding Smithy to hand...");
  replaceCopperWith(smithy, 0, &state);
  printHand(0, &state);
  handPos = getHandPos(0, smithy, &state);
  printf("%d\n", getHandPos(0, smithy, &state));

  return 0;
}

// Modfies hand by replacing Copper with designated card
void replaceCopperWith(int card, int p, struct gameState *state) {
  for (int i = 0; i < state->handCount[p]; i++) {
    if (state->hand[p][i] == copper) {
      state->hand[p][i] = card;
      break;
    }
  }
}

int getHandPos(int p, int card, struct gameState *state) {
  for (int i = 0; i <= state->handCount[p]; i++) {
    if (state->hand[p][i] == card) {
      return i;
    }
  }

  return -1;
}
