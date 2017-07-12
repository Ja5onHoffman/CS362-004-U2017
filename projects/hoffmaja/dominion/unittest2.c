#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


/*********
Unit test for gainCard function.
Add card to a players hand then check for card.
*********/

#undef assert
#define assert(cond) { if (!(cond)) { printf("FAILED TEST\n"); } else { printf("PASS\n"); }}

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int count = 0;
  printf("\n----- UNIT TEST TWO -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);
  printf("Deck before adding card:\n");
  printDeck(0, &state); // Show deck
  count = state.deckCount[0]; // Set original deck count
  printf("\nAdding adventurer card...\n");
  gainCard(adventurer, &state, 1, 0); // Add card
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);

  printf("Deck after adding card:\n");
  printDeck(0, &state); // Show deck with new card

  printf("Deck count should be %d\n", count+1);
  assert(state.deckCount[0] == count+1); // Verify deck increase by one card

  count = 0; // Reset count




  return 0;
}
