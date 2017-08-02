#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"


/*********
Unit test for scoreFor function.
*********/

int errs = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; } else { printf("**PASS**\n"); }}

void addToDeck(int p, int card, struct gameState* state);
void addToDiscard(int p, int card, struct gameState* state);
void replaceCopperWith(int card, int p, struct gameState *state);

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int score = 0;
  printf("\n----- UNIT TEST FOUR: scoreFor() Function -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Default game start. Score should be 3.\n");
  score = scoreFor(0, &state);
  printf("Score: %d\n", score);
  assert(score == 3);

  printf("\nAdding Duchy to deck. Score should be 6.\n");

  addToDeck(0, duchy, &state);
  printDeck(0, &state);
  score = scoreFor(0, &state);
  printf("Score: %d\n", score);
  assert(score == 6);

  printf("\nAdding Province and Curse to discard. Score should be 11.\n");
  addToDiscard(0, province, &state);
  addToDiscard(0, curse, &state);
  printDiscard(0, &state);
  score = scoreFor(0, &state);
  printf("Score: %d\n", score);
  assert(score == 11);

  printf("\nAdding Province to hand. Score should be 17.\n");
  replaceCopperWith(province, 0, &state);
  printHand(0, &state);
  score = scoreFor(0, &state);
  printf("Score: %d\n", score);
  assert(score == 17);

  printf("\nAdding Gardens to hand, deck and discard. Score should be 17.\n");
  addToDeck(0, gardens, &state);
  addToDiscard(0, gardens, &state);
  replaceCopperWith(gardens, 0, &state);
  printDeck(0, &state);
  printDiscard(0, &state);
  printHand(0, &state);
  score = scoreFor(0, &state);
  printf("Score: %d\n", score);
  assert(score == 17);


  printf("\n\n\n");
  printf("UNIT TEST 4 - Total failed tests: %d of 5\n\n", errs);


  return 0;

}

// Adds directly to discard
void addToDiscard(int p, int card, struct gameState *state) {
  state->discard[p][state->discardCount[p]] = card;
  state->discardCount[p] += 1;
}

// Adds direclty to deck
void addToDeck(int p, int card, struct gameState *state) {
  state->deck[p][state->deckCount[p]] = card;
  state->deckCount[p] += 1;
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
