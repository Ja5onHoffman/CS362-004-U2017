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

int main() {
  struct gameState state;
  struct gameState oldState;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int handPos = -1;
  int currentPlayer = 0;
  printf("\n----- CARD TEST ONE -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Adding Smithy to Player 1 hand...\n");
  replaceCopperWith(smithy, 0, &state);
  printHand(0, &state);
  handPos = getHandPos(0, smithy, &state);

  printf("Recording game state...\n");
  memcpy(&oldState, &state, sizeof(struct gameState));

  int oldCount = state.handCount[0];
  printf("Player 1's hand count is now %d\n", oldCount);
  printf("Playing Smithy...\n");
  int hp = getHandPos(0, smithy, &state);
  playSmithy(&currentPlayer, &hp, &state);
  printf("Drawing three cards...\n");
  printf("Player 1's hand count should now be %d (old count \
    minus Smithy plus three).\n", oldCount + 2);
  printf("Hand count: %d\n", state.handCount[0]);
  assert(state.handCount[0] == oldCount + 2);

  printf("Player 2 state should be unchanged.\n");
  printf("Checking Player 2 hand...\n");
  assert(!memcmp(&state.hand[1], &oldState.hand[1], state.handCount[1] * sizeof(int)));
  printf("Checking Player 2 hand count...\n");
  assert(state.handCount[1] == oldState.handCount[1]);
  printf("Checking Player 2 deck...\n");
  assert(!memcmp(&state.deck[1], &oldState.deck[1], state.deckCount[1] * sizeof(int)));
  printf("Checking Player 2 deck count...\n");
  assert(state.deckCount[1] == oldState.deckCount[1]);
  printf("Checking Player 2 discard...\n");
  assert(!memcmp(&state.discard[1], &oldState.discard[1], state.discardCount[1] * sizeof(int)));

  printf("Kingdom and Victory piles should be unchanged.\n");
  printf("Checking Kingdom pile.\n");


  printf("\n\n\n");
  printf("CARD TEST 1 - Total failed tests: %d\n", errs);

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
