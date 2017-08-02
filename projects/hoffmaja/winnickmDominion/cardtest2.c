#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

int errs = 0;
int tests = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; tests++; } else { printf("**PASS**\n"); tests++; }}

void replaceCopperWith(int card, int p, struct gameState *state);
void verifyTopThree(int p, struct gameState *state);
void verifyDiscard(int *tempHand, int p, int *z, struct gameState *state);

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int currentPlayer = 0;

/*
  Ass. 5: CardEffect variables contained int winnick's adventurer function
*/
  // Additional variables from cardEffect
  // int temphand[MAX_HAND]; // moved above the if statement
  // memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length
  // int drawntreasure=0;
  // int cardDrawn;
  // int z = 0;
  printf("\n----- CARD TEST TWO: Adventurer Card -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Adding Adventurer to Player 1 hand...\n");
  replaceCopperWith(adventurer, 0, &state);
  printHand(0, &state);
  printDeck(0, &state);
  printDiscard(0, &state);
  printf("Playing Adventurer...\n");
  // playAdventurer(&z, &drawntreasure, &currentPlayer, temphand, &cardDrawn, &state);
  int z = adventurerEffect(&state);
  printHand(0, &state);
  printDeck(0, &state);
  printDiscard(0, &state);

  printf("All drawn cards should be treasure cards. Testing...\n");
  verifyTopThree(0, &state);

  // for (int i = 0; i < MAX_HAND; i++) {
  //   if (temphand[i] != '\0') {
  //     z++;
  //   }
  // }

  printf("All non-treasure discarded cards should \
  be in in Discard pile. Testing...\n");
  // verifyDiscard(&temphand, 0, &z, &state);

  printf("Testing %d discarded cards.\n", state.discardCount[0]);
  printDiscard(0, &state);
  // for (int i = 0; i < z; i++) {
  //   printf("\nCard %d\n", i);
  // }
  // This will be estate at beginning of game
  assert(state.discard[0][0] == estate);

  printf("\n\n\n");
  printf("CARD TEST 2 - Total failed tests: %d of %d\n", errs, tests);

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

// Verifies the cards drawn by Adventurer are all treasure careds
void verifyTopThree(int p, struct gameState *state) {
  int cards[3] = { 0 }; // init to 0s
  int c = 0, flag = 0; // index for cards
  int i = state->handCount[p] - 1;
  for (i; i >= state->handCount[p] - 3; i--) {
    if (state->hand[p][i] != copper && state->hand[p][i] != silver && state->hand[p][i] != gold) {
      flag = 1;
      cards[c] = state->hand[p][i];
      c++;
    }
  }

  if (flag) {
    printf("FAILED TEST: Card other than trasure drawn.\n");
    errs++;
    tests++;
    printHand(0, state);
  } else {
    printf("PASSED TEST: All treasure cards drawn.\n");
    tests++;
    printHand(0, state);
  }
}

void verifyDiscard(int *tempHand, int p, int *z, struct gameState *state) {
  printf("Testing %d discarded cards.\n", state->discardCount[p]);
  printDiscard(0, state);
  for (int i = 0; i < *z; i++) {
    printf("\nCard %d\n", i);
    assert(state->discard[p][i] == tempHand[i]);
  }
}
