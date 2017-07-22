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

void replaceCopperWith(int card, int p, struct gameState *state);

int main() {
  struct gameState staticState;
  int numPlayers = 0;
  int player = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  // int seed = 9;
  // int currentPlayer = 0;

  // Additional variables from cardEffect
  // int temphand[MAX_HAND];// moved above the if statement
  // memset(temphand, '\0', sizeof(temphand)); // Initialize to null for determining length
  // int drawntreasure=0;
  // int cardDrawn;
  // int z = 0;


  // Loop some type of test
  // Set up random
  SelectStream(1);
  PlantSeeds(time(NULL));
  for (int i = 0; i < 10; i++) {
    struct gameState state;
    SelectStream(i+1); // +1 so we don't have to enter a seed
    numPlayers = floor(Random() * 5) + 2; // Two to six players
    printf("numPlayers: %d\n", numPlayers);
    player = floor(Random() * 5); //Get random player
    printf("player: %d\n", player);

    initializeGame(numPlayers, k, i, &state);
    
    // Add adventurer to hand
    if(addCardToHand(player, adventurer, &state) == SUCCESS) {
      printHand(player, &state);
    }
  }


  // play adventurer with random inputs  -




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
