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
  int drawntreasure=0;
  int cardDrawn;
  int z;
  printf("\n----- CARD TEST TWO -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Adding Adventurer to Player 1 hand...\n");
  replaceCopperWith(adventurer, 0, &state);
  printHand(0, &state);
  printDeck(0, &state);
  printDiscard(0, &state);
  printf("Playing Adventurer...\n");
  playAdventurer(&z, &drawntreasure, &currentPlayer, temphand, &cardDrawn, &state);
  printHand(0, &state);
  printDeck(0, &state);
  printDiscard(0, &state);
  printf("Add drawn cards should be treasure cards. Testing...\n");
  verifyTopThree(0, &state);


  // assert temphand cards are in discard




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
    printHand(0, state);
  } else {
    printf("PASSED TEST: All treasure cards drawn.\n");
    printHand(0, state);
  }
}
