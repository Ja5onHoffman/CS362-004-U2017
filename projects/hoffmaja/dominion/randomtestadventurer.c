#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define PASS 1
#define FAIL 0

int errs = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; } else { printf("**PASS**\n"); }}

void replaceCopperWith(int card, int p, struct gameState *state);
void verifyTopThree(int p, struct gameState *state);
void verifyDiscard(int *tempHand, int p, int *z, struct gameState *state);
void testAdventurer(int seed);

int main() {
  int numTests = 2000;
  // test adventurer in loop
  SelectStream(0);
  PlantSeeds(9999);
  printf("\n----- RANDOM TEST: Adventurer Card -----\n\n");
  for (int i = 0; i < numTests; i++) {
    testAdventurer(i);
  }

  printf("CARD TEST 2 - Total failed tests: %d out of %d\n", errs, numTests);
}


void testAdventurer(int seed) {
  SelectStream(seed+1); // In case see = 0;
  struct gameState staticState;
  int numPlayers = 0;
  int player = 0;
  int currentPlayer = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

  // Additional variables from cardEffect
  int temphand[MAX_HAND]; // moved above the if statement
  memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length
  int drawntreasure=0;
  int cardDrawn; // Empty int to hold card
  int z = 0; // Counter for temp hand

  // Loop some type of test
  // Set up random


  struct gameState state;
  numPlayers = floor(Random() * 4) + 1; // Two to four players
  printf("numPlayers: %d\n", numPlayers);
  player = floor(Random() * numPlayers + 1); //Get random player
  printf("player: %d\n", player);

  initializeGame(numPlayers, k, 9, &state);

  // Add adventurer
  replaceCopperWith(adventurer, player, &state);

  // Play adventurer with randomly generated player and state
  playAdventurer(&z, &drawntreasure, &player, temphand, &cardDrawn, &state);
  // All drawn cards should be treasure cards
  verifyTopThree(player, &state);
  // All non-treasure discarded cards shoudl be in Discard pile
  verifyDiscard(&temphand, 0, &z, &state);
}


// Verifies the cards drawn by Adventurer are all treasure cards
void verifyTopThree(int p, struct gameState *state) {
  int cards[3] = { 0 }; // init to 0s
  int c = 0, flag = PASS; // index for cards
  int i = state->handCount[p] - 1;
  for (i; i >= state->handCount[p] - 3; i--) {
    if (state->hand[p][i] != copper && state->hand[p][i] != silver && state->hand[p][i] != gold) {
      flag = FAIL;
      cards[c] = state->hand[p][i];
      c++;
    }
  }
  assert(flag);
}

void verifyDiscard(int *tempHand, int p, int *z, struct gameState *state) {
  printf("Testing %d discarded cards.\n", state->discardCount[p]);
  printDiscard(0, state);
  int flag = PASS;
  for (int i = 0; i < *z; i++) {
    printf("\nCard %d\n", i);
    if (state->discard[p][i] != tempHand[i]) {
      flag = FAIL;
    }
  }
  assert(flag);
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
