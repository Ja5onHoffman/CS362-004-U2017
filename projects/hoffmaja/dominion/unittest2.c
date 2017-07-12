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
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); } else { printf("**PASS**\n"); }}

int main() {
  struct gameState state;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 9;
  int count = 0, supp = 0;
  printf("\n----- UNIT TEST TWO -----\n\n");

  // Initialize game
  initializeGame(numPlayers, k, seed, &state);

  printf("Checking 'add to deck' flag\n");
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);
  printf("Deck before adding card:\n");
  printDeck(0, &state); // Show deck
  count = state.deckCount[0]; // Set original deck count
  supp = supplyCount(adventurer, &state);;
  printf("\nAdding adventurer card...\n");
  gainCard(adventurer, &state, 1, 0); // Add card
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);

  printf("Deck after adding card:\n");
  printDeck(0, &state); // Show deck with new card

  printf("Deck count should be %d\n", count+1);
  assert(state.deckCount[0] == count+1); // Verify deck increase by one card
  printf("Supply of card should be %d\n", supp-1);
  assert(supplyCount(adventurer, &state) == supp-1);
  printf("Hand should contain adventureer at position %d\n", state.deckCount[0]-1);
  assert(state.deck[0][state.deckCount[0]-1] == adventurer);

  // printf("Deck should contain adventurer");
  // assert(state.supply)


  count = 0; // Reset count

  printf("\nChecking 'add to discard' flag\n");

  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);

  printf("Discard before discarding card:\n");
  printDiscard(0, &state);
  count = state.discardCount[0]; // Set original discard count
  gainCard(adventurer, &state, 0, 0);
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);
  printf("Discard after discarding card:\n");
  printDiscard(0, &state);

  printf("Discard count should be %d\n", count+1);
  assert(state.discardCount[0] == count+1);

  count = 0; // Reset count





  return 0;
}
