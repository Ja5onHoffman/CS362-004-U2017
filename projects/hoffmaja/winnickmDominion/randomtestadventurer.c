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
int tests = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; tests++; } else { printf("**PASS**\n"); tests++; }}

void replaceCopperWith(int card, int p, struct gameState *state);
void verifyTopThree(int p, struct gameState *state);
void verifyDiscard(int *tempHand, int p, int *z, struct gameState *state);
void testAdventurer(int seed);
void arrayShuffle(int arr[], int n);

int main() {
  int numTests = 1;
  SelectStream(0);
  PlantSeeds(9999);
  printf("\n----- RANDOM TEST: Adventurer Card -----\n\n");
  // Test adventurer in loop
  for (int i = 0; i < numTests; i++) {
    printf("\n\nTest #%d\n", i);
    testAdventurer(i);
  }

  printf("RANDOM TEST: Adventurer - Total failed asserts: %d out of %d\n", errs, tests);

  return 0;
}


void testAdventurer(int seed) {
  SelectStream(seed+1); // In case seed = 0;
  struct gameState staticState;
  int numPlayers = 0;
  int player = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

  // Additional variables from cardEffect
  int temphand[MAX_HAND]; // moved above the if statement
  memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length
  int drawntreasure=0;
  int cardDrawn; // Empty int to hold card
  int z = 0; // Counter for temp hand

  struct gameState state;
  numPlayers = floor(Random() * 3) + 2; // Two to four players
  player = floor(Random() * numPlayers); //Get random player

  initializeGame(numPlayers, k, seed+1, &state);
  memcpy(&staticState, &state, sizeof(struct gameState));
  printHand(player, &state);
  // Add adventurer
  addCardToHand(player, adventurer, &state);

  // Play adventurer with randomly generated player and state
  // playAdventurer(&z, &drawntreasure, &player, temphand, &cardDrawn, &state);

  z = adventurerEffect(&state);
  printf("Verifying player %d's drawn cards are treasure cards\n", player);
  verifyTopThree(player, &state);
  printf("Verifying all non-treasure discarded cards are in Discard pile\n");
  // verifyDiscard(temphand, 0, z, &state); won't work without temphand

  // Empty discard and check shuffle
  printf("Setting deckCount to zero and verifying shuffle\n");
  state.deckCount[player] = 0;
  // playAdventurer(&z, &drawntreasure, &player, temphand, &cardDrawn, &state);
  adventurerEffect(&state);
  // State and static state should be different
  assert(!memcmp(&state.deck[player], &staticState.deck[player], staticState.deckCount[player] * sizeof(int)));
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
  int flag = PASS;
  for (int i = 0; i < *z; i++) {
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

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrayShuffle(int arr[], int n) {
    srand(time(NULL));
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}
