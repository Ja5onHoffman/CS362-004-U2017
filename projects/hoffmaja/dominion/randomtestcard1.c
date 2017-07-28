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
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; } else { printf("**PASS**\n"); }}

void replaceCopperWith(int card, int p, struct gameState *state);
void testPlayedCards(int card, struct gameState *state);
void arrayShuffle(int arr[], int n);
void testSalvager(int seed);

int main() {
  int numTests = 2000;
  // Test Salvager in loop
  SelectStream(0);
  PlantSeeds(9999);

  for (int i = 0; i < numTests; i++) {
    testSalvager(numTests);
  }

  // Need to multiply numtests by number of asserts
  printf("RANDOM TEST: Salvager - Total failed tests: %d out of %d\n", errs, numTests*5);
  return 0;
}

void testSalvager(int seed) {
  SelectStream(seed+1);
  int k_cards[19];
  struct gameState state;
  int numPlayers = 0;
  int player = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

  printf("\n----- RANDOM TEST: Salvager Card -----\n\n");

  // Fill k_cards
  // for (int i = 0; i < 19; i++) {
  //   k_cards[i] = i+7;
  // }
  //
  // // Get a random ten kingdom cards by using subset of shuffled array
  // arrayShuffle(k_cards, 19);
  // for (int i = 0; i < 10; i++) {
  //   k[i] = k_cards[i];
  // }

  numPlayers = floor(Random() * 3) + 2; // Two to four players
  player = floor(Random() * numPlayers + 1); //Get random player
  // Initialize game
  initializeGame(numPlayers, k, seed+1, &state);

  printHand(player, &state);
  // Add random card to hand
  int c = floor(Random() * 10);
  int randCard = k[c];
  int cost = getCost(randCard);
  // replaceCopperWith(randCard, player, &state);
  addCardToHand(player, randCard, &state);
  printHand(player, &state);
  // Add salvager to hand
  // replaceCopperWith(salvager, player, &state);
  addCardToHand(player, salvager, &state);
  printHand(player, &state);
  // Play salvager
  int salvagerPos = getHandPos(player, salvager, &state);
  int randPos = getHandPos(player, randCard, &state);

  int buysBefore = state.numBuys;
  int coinsBefore = state.coins;
  playSalvager(&player, &salvagerPos, &randPos, &state);
  // Num buys greater (consider buysBefore + 1)
  assert(state.numBuys > buysBefore);
  // Gain card value
  assert(state.coins == coinsBefore + getCost(randCard));
  // Salvager in played cards
  assert(state.playedCards[0] == salvager);
  // Played cards increase by 1
  assert(state.playedCardCount == 1);
  // Card no longer in hand
  assert(state.hand[0][randPos] != randCard);


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

// Modfies hand by replacing Copper with designated card
void replaceCopperWith(int card, int p, struct gameState *state) {
  for (int i = 0; i < state->handCount[p]; i++) {
    if (state->hand[p][i] == copper) {
      state->hand[p][i] = card;
      break;
    }
  }
}
