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
int errs = 0;
#undef assert
#define assert(cond) { if (!(cond)) { printf("--FAILED TEST--\n"); errs++; } else { printf("**PASS**\n"); }}

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

  printf("***** Checking 'add to deck' flag ********\n\n");
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

  count = 0; // Reset count
  supp  = 0; // Reset supply

  printf("\n********* Checking 'add to discard' flag *********\n\n");

  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);

  printf("Discard before discarding card:\n");
  printDiscard(0, &state);
  count = state.discardCount[0]; // Set original discard count
  supp = supplyCount(adventurer, &state);
  gainCard(adventurer, &state, 0, 0);
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);
  printf("Discard after discarding card:\n");
  printDiscard(0, &state);

  printf("Discard count should be %d\n", count+1);
  assert(state.discardCount[0] == count+1);
  printf("Supply count should be %d\n", supp-1);
  assert(supplyCount(adventurer, &state) == supp-1);
  printf("Discard should contain adventurer at position %d\n", state.discardCount[0]-1);
  assert(state.discard[0][state.discardCount[0]-1] == adventurer);

  count = 0; // Reset count
  supp  = 0;  // Reset supply

  printf("\n********* Checking 'add to hand' flag *********\n\n");

  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);
  printf("Hand before adding card:\n");
  printHand(0, &state);
  count = state.handCount[0]; // Set original hand count
  supp = supplyCount(adventurer, &state);;
  printf("\nAdding adventurer card...\n");
  gainCard(adventurer, &state, 2, 0); // Add card
  printf("Deck count: %d\n", state.deckCount[0]);
  printf("Hand count: %d\n", state.handCount[0]);
  printf("Discard count: %d\n\n", state.discardCount[0]);

  printf("Hand after adding card:\n");
  printHand(0, &state); // Show hand with new card

  printf("Hand count should be %d\n", count+1);
  assert(state.handCount[0] == count+1); // Verify hand increase by one card
  printf("Supply of card should be %d\n", supp-1);
  assert(supplyCount(adventurer, &state) == supp-1);
  printf("Hand should contain adventurer at position %d\n", state.handCount[0]-1);
  assert(state.hand[0][state.handCount[0]-1] == adventurer);

  count = 0; // Reset count
  supp  = 0; // Reset supply

  printf("\n******** Checking for non-card ********\n\n");

  printf("Adding nonexistent card....\n");
  int noncard = -1;
  int err = gainCard(noncard, &state, 0, 0);

  printf("Function should return -1\n");
  assert(err == -1);

  printf("\n\n\n");
  printf("Total failed tests: %d\n\n", errs);



  return 0;
}
