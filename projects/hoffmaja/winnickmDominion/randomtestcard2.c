#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

int errs = 0;
int tests = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; tests++; } else { printf("**PASS**\n"); tests++; }}

void replaceCopperWith(int card, int p, struct gameState *state);
void testPlayedCards(int card, struct gameState *state);
void arrayShuffle(int arr[], int n);
void testSmithy(int seed);
int getHandPos(int p, int card, struct gameState *state);

int main() {
  int numTests = 10000;
  // Test Salvager in loop
  SelectStream(0);
  PlantSeeds(9999);

  for (int i = 0; i < numTests; i++) {
    printf("\n\nTest #%d\n", i);
    testSmithy(i);
  }


  // Need to multiply numtests by number of asserts
  printf("RANDOM TEST: Smithy - Total failed asserts: %d out of %d\n", errs, tests);
  return 0;
}

void testSmithy(int seed) {
  struct gameState state;
  struct gameState oldState;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int handPos = -1;
  int numPlayers = 0;
  int player = 0;
  printf("\n----- RANDOM TEST: Smithy Card -----\n\n");

  numPlayers = floor(Random() * 3) + 2; // Two to four players
  player = floor(Random() * numPlayers); //Get random player

  // Initialize game
  initializeGame(numPlayers, k, seed+1, &state);

  // Record state
  memcpy(&oldState, &state, sizeof(struct gameState));
  addCardToHand(player, smithy, &state);
  // Get hand position
  int oldCount = state.handCount[player];
  handPos = getHandPos(player, smithy, &state);
  // Play smithy
  // playSmithy(&player, &handPos, &state);
  smithyEffect(&state, handPos);
  // Assert three cards drawn
  printf("Assert three cards were drawn by player %d\n", player);
  assert(state.handCount[player] == oldCount + 2);

  // For each player, verify that the state is unchanged.
  printf("For each other player, verify that the state is unchanged.\n");
  for (int i = 0; i < numPlayers; i++) {
    if (i != player) {
      printf("Player %d hand, deck and discard.\n", i);
      assert(!memcmp(&state.hand[i], &oldState.hand[i], state.handCount[i] * sizeof(int)));
      assert(state.handCount[i] == oldState.handCount[i]);
      assert(!memcmp(&state.deck[i], &oldState.deck[i], state.deckCount[i] * sizeof(int)));
      assert(state.deckCount[i] == oldState.deckCount[i]);
      assert(!memcmp(&state.discard[i], &oldState.discard[i], state.discardCount[i] * sizeof(int)));
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
