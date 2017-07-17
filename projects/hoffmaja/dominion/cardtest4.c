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
void addFiveToDeck(int p, struct gameState *state);

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

  printf("Discarding four cards to make room for P1 draws...\n");
  for (int i = 0; i < 4; i++) {
    discardCard(i, 0, &state);
  }

  printHand(1, &state);
  printf("Adding Council Room to hand...\n");
  replaceCopperWith(council_room, 0, &state);

  int cp = getHandPos(0, council_room, &state);
  int oldCount = state.handCount[0];
  int oldBuys = state.numBuys;


  int oldCount2 = state.handCount[1];
  printHand(1, &state);

  printf("Playing Council Room...\n");
  playCouncilRoom(&currentPlayer, &cp, &state);

  printf("\nVerifying four cards drawn by current player...\n");
  printf("Prevous hand count: %d\n", oldCount);
  printf("New hand count (minus played Council Room): %d\n", state.handCount[0]);
  assert(state.handCount[0] == oldCount + 3);

  printf("\nVerifying number of buys increased by one...\n");
  printf("Previous buys: %d\n", oldBuys);
  printf("New buys: %d\n", state.numBuys);
  assert(state.numBuys == oldBuys + 1);

  printf("\nVerifying P2 hand count increased by 1...\n");
  printf("Old hand count: %d\n", oldCount2);
  printf("New hand count: %d\n", state.handCount[1]);
  assert(state.handCount[1] == oldCount2 + 1);


  printf("\n\n\n");
  printf("CARD TEST 4 - Total failed tests: %dn\n", errs);

  printPlayed(0, &state);
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

// int deck[MAX_PLAYERS][MAX_DECK];
// int deckCount[MAX_PLAYERS];

void addFiveToDeck(int p, struct gameState *state) {
  for (int i = 0; i < 5; i++) {
    state->deck[p][state->deckCount[p]] = gold;
    state->deckCount[p]++;
  }
}
