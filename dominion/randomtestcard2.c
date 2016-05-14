#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 10

//This randomly tests smithy

int main() {

	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

	  int i, j, n, players, player, handCount, deckCount, seed, address, handPos, numActions, storeActions;
	  struct gameState state;
	  struct gameState stat;
	  struct gameState sta;


	  for (i = 0; i < MAX_TESTS; i++) {
			players = (rand() % 4) + 1;
	 		player = rand() % players;
	 		numActions = (rand() % 25) + 1;


	 	  seed = rand();		//pick random seed
	 	  initializeGame(players, k, seed, &state);	//initialize Gamestate

	 	   //Initiate valid state variables
	 		state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	 		state.discardCount[player] = rand() % MAX_DECK;
	 		state.handCount[player] = rand() % MAX_HAND;
	 		state.numPlayers = players;
	 		state.whoseTurn = player;
	 		state.numActions = numActions;

			handCount = state.handCount[player];
			storeActions = state.numActions;
			//printf("Preactions: %d  PreCount: %d\n", storeActions, handCount);
		  cardEffect(village, 0, 0, 0, &state, 0, 0);		//Run adventurer card
			//printf("Postactions: %d  PostCount: %d\n", state.numActions, state.handCount[player]);
			storeActions += 2;
			//handCount += 1;

			if(storeActions == state.numActions && handCount == state.handCount[player])
				printf("smithy Test passed\n");
			else
				printf("smithy Test failed\n");


	  }

	  printf("Tests Complete\n");

	  return 0;
}
