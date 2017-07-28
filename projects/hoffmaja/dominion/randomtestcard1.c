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
void testPlayedCards(int card, struct gameState *state);
shuffle(int arr[], int n);
void testSalvager(int seed);

int main() {
  int numTests = 2000;
  // Test Salvager in loop
  SelectStream(0);
  PlantSeeds(9999);
  printf("\n----- RANDOM TEST: Adventurer Card -----\n\n");
  for (int i = 0; i < numTests; i++) {
    testSalvager(i);
  }


  printf("RANDOM TEST: Salvager - Total failed tests: %d out of %d\n", errs, numTests);

}

void testSalvager(int seed) {
  SelectStream(seed+1);
  int k_cards[19];
  struct gameState state;
  int numPlayers = 0;
  int player = 0;
  int k[10];
  int seed = 9;

  // Additional variables from cardEffect
  int temphand[MAX_HAND];// moved above the if statement
  memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length

  printf("\n----- RANDOM TEST: Salvager Card -----\n\n");

  // Fill k_cards
  for (int i = 7; i < 27; i++) {
    k_cards[i] = i;
  }

  // Get a random ten kingdom cards by using subset of shuffled array
  shuffle(k_cards, 19);
  for (int i = 0; i < 10; i++) {
    k[i] = k_cards[i];
  }

  numPlayers = floor(Random() * 4) + 1; // Two to four players
  player = floor(Random() * numPlayers + 1); //Get random player
  // Initialize game
  initializeGame(numPlayers, k, seed, &state);


  // Add random card to hand
  int randCard = k[floor(Random() * 10)];
  int cost = getCost(randCard);
  replaceCopperWith(randCard, player, &state);
  // Add salvager to hand
  replaceCopperWith(salvager, player, &state);
  // Play salvager
  int salvagerPos = getHandPos(0, salvager, &state);
  int randPos = getHandPos(0, adventurer, &state);

  int buysBefore = state.numBuys;
  int coinsBefore = state.coins;
  playSalvager(&player, &salvager, &randPos, &state);

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

void shuffle(int arr[], int n) {

    srand (time(NULL));

    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}
