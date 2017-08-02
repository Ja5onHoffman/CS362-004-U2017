#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h" // For cardEffect
#include "interface.h"
#include "rngs.h"

int errs = 0;
int tests = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; tests++; } else { printf("**PASS**\n"); tests++; }}

void replaceCopperWith(int card, int p, struct gameState *state);
void testPlayedCards(int card, struct gameState *state);
int getHandPos(int p, int card, struct gameState *state);

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int currentPlayer = 0;

  // Additional variables from cardEffect
  int temphand[MAX_HAND];// moved above the if statement
  memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length


  printf("\n----- CARD TEST 3: Salvager Card -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);


  printf("Adding Salvager to Player 1 hand...\n");
  replaceCopperWith(salvager, 0, &state);
  printf("Adding Adventurer to be discarded...\n");
  replaceCopperWith(adventurer, 0, &state);
  printHand(0, &state);
  printf("Playing Salvager...\n");
  int salvagerPos = getHandPos(0, salvager, &state);
  int adventurerPos = getHandPos(0, adventurer, &state);

  int buysBefore = state.numBuys;
  int coinsBefore = state.coins;
  // playSalvager(&currentPlayer, &salvagerPos, &adventurerPos, &state);
  int b = 0;
  cardEffect(salvager, adventurer, 0, 0, &state, salvagerPos, &b);

  printf("Verifying buys increase by 1...\n");
  printf("Buys before playing Salvager: %d\n", buysBefore);
  printf("Buys after playing Salvager: %d\n", state.numBuys);
  assert(state.numBuys > buysBefore);

  printf("\nVerifying coins increase by amount equal to trashed card...\n");
  printf("(Increase should be 6 for discarding Adventurer)\n");
  printf("Coins before playing Salvager: %d\n", coinsBefore);
  printf("Coins after playing Salvager: %d\n", state.coins);
  assert(state.coins == coinsBefore + 6);

  printf("\nVerifying Salvager sent to played pile...\n");
  printPlayed(0, &state);
  testPlayedCards(salvager, &state);
  printf("\nVerifying that no other cards exist in played pile...\n");
  printf("Played count: %d\n", state.playedCardCount);
  assert(state.playedCardCount == 1);

  printf("\nVerifying trashed card is no longer in hand...\n");
  printHand(0, &state);
  assert(state.hand[0][adventurerPos] != adventurer);


  printf("\n\n\n");
  printf("CARD TEST 3 - Total failed tests: %d\n", errs);

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

// Testing played cards via loop in case bug puts card in
// incorrect position
void testPlayedCards(int card, struct gameState *state) {
  for (int i = 0; i < state->playedCardCount; i++) {
    if (state->playedCards[i] == card) {
      printf("**PASSED**\n");
      return;
    }
  }

  printf("--FAILED TEST--\n");
  errs++;
}

int getHandPos(int p, int card, struct gameState *state) {
  for (int i = 0; i <= state->handCount[p]; i++) {
    if (state->hand[p][i] == card) {
      return i;
    }
  }

  return -1;
}
