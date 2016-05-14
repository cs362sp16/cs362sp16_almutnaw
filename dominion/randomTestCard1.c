//////////////////////////
// Testing villag card //
//////////////////////////

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 100
#define CARD_TESTS 10

int main(int argc, char *argv[]) {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	int i, j, n, players, player, handCount, deckCount, seed, address;
	int i_prime;
	
	struct gameState state;
	if (argc != 2)
	{
		printf("Enter a seed:\n");
		scanf("%d", &seed);
	}
	else{
		seed = atoi(argv[1]);
	}

	srand(seed);

	for (i = 0; i < MAX_TESTS; i++) {

		players = rand() % 4;

		seed = rand();

		initializeGame(players, k, seed, &state);	
		for (player = 0; player < players; player++)
		{


			state.deckCount[player]    = rand() % MAX_DECK; 
			state.discardCount[player] = rand() % MAX_DECK;
			state.handCount[player]    = rand() % MAX_HAND;

			//Copy state variables initial values
			handCount = state.handCount[player];
			deckCount = state.deckCount[player];

			// add random cards to hand based on handCount value
			for (j = 0; j < handCount; j++)
			{
				state.hand[player][j] = rand() % 28; // Add a random card (of value 0-27) to the hand
			}
			if (seed % 3 == 0) {
				state.deckCount[player] = 0;
			}

			int card_tests = rand() % CARD_TESTS;
			for (i_prime = 0; i_prime < card_tests; i_prime++)
			{
				switch (rand() % 2)
				{
					case 0:
						{

							printf("Running village\n");
							int prev_actions = state.numActions;

							cardEffect(village, 1, 1, 1, &state, 0, 0);		//Run adventurer card

							// since we discard village, and then draw a card, the hand size should stay the same
							if (state.handCount[player] != handCount)
							{
								fprintf(stdout, "Hand count changed. Count now %s than original value of %d. Count now %d\n",
										state.handCount[player] > handCount ? "greater" : "less",
										handCount, state.handCount[player]);
							}

							if (state.hand[player][0] != -1)
							{
								fprintf(stdout, "Card not properly discarded from hand\n");
								printf("first card: %d\n", state.hand[player][0]);
							}

							// check actions
							if (state.numActions != prev_actions + 2)
							{
								printf(stdout, "Actions should be %d+2, is %d\n", prev_actions, state.numActions);
							}


						}

					case 1:
						{
							// play the top card in the hand, and assume it operates correctly.
							// We are testing village, not the other cards.
							// printf("Running other card\n");
							// printf("card: %d\n", state.hand[player][0]);
							cardEffect(state.hand[player][0], 1, 1, 1, &state, 0, 0);
						}
				}
			}
		}

	}

	printf("Tests Complete\n");

	return 0;
}
