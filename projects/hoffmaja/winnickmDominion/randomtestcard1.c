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
void testSalvager(int seed);

int main() {
  int numTests = 10000;
  // Test Salvager in loop
  SelectStream(0);
  PlantSeeds(9999);

  for (int i = 0; i < numTests; i++) {
    printf("\n\nTest #%d\n", i);
    testSalvager(numTests);
  }

  printf("RANDOM TEST: Salvager - Total failed asserts: %d out of %d\n", errs, tests);
  return 0;
}

void testSalvager(int seed) {
  SelectStream(seed+1);
  int k_cards[19];
  struct gameState state;
  int numPlayers = 0;
  int player = 0;
  int k[10];
  // int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
  //   sea_hag, tribute, smithy, council_room};

  printf("\n----- RANDOM TEST: Salvager Card -----\n\n");

  // Fill k_cards
  for (int i = 0; i < 19; i++) {
    k_cards[i] = i+7;
  }

  // Get a random ten kingdom cards by using subset of shuffled array
  arrayShuffle(k_cards, 19);
  for (int i = 0; i < 10; i++) {
    k[i] = k_cards[i];
  }

  numPlayers = floor(Random() * 3) + 2; // Two to four players
  player = floor(Random() * numPlayers); //Get random player
  // Initialize game
  initializeGame(numPlayers, k, seed+1, &state);
  // Add random card to hand
  int c = floor(Random() * 10);
  int randCard = k[c];
  int cost = getCost(randCard);
  addCardToHand(player, randCard, &state);
  // Add salvager to hand
  addCardToHand(player, salvager, &state);
  // Play salvager
  int salvagerPos = getHandPos(player, salvager, &state);
  int randPos = getHandPos(player, randCard, &state);

  printf("Salvager added to player %d's hand. Playing...\n", player);
  int buysBefore = state.numBuys;
  int coinsBefore = state.coins;
  playSalvager(&player, &salvagerPos, &randPos, &state);

  printf("Assert buys increase after playing Salvager card\n");
  assert(state.numBuys > buysBefore);
  printf("Assert coins gained equal to discarded card\n");
  assert(state.coins == coinsBefore + getCost(randCard));
  printf("Assert Salvager is in player %d's played cards\n", player);
  assert(state.playedCards[player] == salvager);
  printf("Assert played card count increases by one\n");
  assert(state.playedCardCount == 1);
  printf("Assert salvager is no longer in player hand\n");
  assert(state.hand[player][randPos] != randCard);
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
