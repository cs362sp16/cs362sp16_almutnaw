#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 100
#define CARD_TESTS 10

//This randomly tests Adventurer

int main() {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	int i, j, n, players, player, handCount, deckCount, seed, address;
	int i_prime;

	struct gameState state;

	printf("Running Random Adventurer Test\n");

	for (i = 0; i < MAX_TESTS; i++) {

		players = rand() % 4;

		seed = rand();

		initializeGame(players, k, seed, &state);	//initialize Gamestate 
		for (player = 0; player < players; player++)
		{

			//Initiate valid state variables
			state.deckCount[player]    = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
			state.discardCount[player] = rand() % MAX_DECK;
			state.handCount[player]    = rand() % MAX_HAND;
			//Copy state variables initial values
			handCount = state.handCount[player];
			deckCount = state.deckCount[player];
			// add random cards to hand based on handCount value
			for (j = 0; j < handCount; j++)
			{
				state.hand[player][j] = rand() % 28; // Add a random card(value 0-27) to hand
			}

			// count the treasure cards in the deck
			//1 in 3 chance of making empty deck for coverage

			if (seed % 3 == 0) {
				state.deckCount[player] = 0;
			}
			/* Run a random number of cards from the player hand */
			int card_tests = rand() % CARD_TESTS;
			for (i_prime = 0; i_prime < card_tests; i_prime++)
			{
				/* Randomly decide to run the top card in the hand, or run an adventurer card */
				switch (rand() % 2)
				{
					case 0:
						{
							int count = 0;
							for (j = 0; j < deckCount; j++)
							{
								int card = state.deck[player][j];
								if (card == copper || card == silver || card == gold)
									++count;
							}

							int hand_count = 0;
							for (j = 0; j < handCount; j++)
							{
								int card = state.hand[player][j];
								if (card == copper || card == silver || card == gold)
									++hand_count;
							}
							cardEffect(adventurer, 1, 1, 1, &state, 0, 0);		//Run adventurer card

							/* Test the output to see if it correct*/
							// count the treasure cards in the deck after the call
							int count_after = 0;
							for (j = 0; j < state.deckCount[player]; j++)
							{
								int card = state.deck[player][j];
								if (card == copper || card == silver || card == gold)
									++count_after;
							}

							// count treasure cards in the hand after the call
							int hand_count_after = 0;
							for (j = 0; j < state.handCount[player]; j++)
							{
								int card = state.hand[player][j];
								if (card == copper || card == silver || card == gold)
									++hand_count_after;
							}


							/* Check the manual count of all treasure cards in the deck. At most 2 should be removed 
							 * Also check to see if the corresponding number of treasure cards were added to the hand */
							if (count >= 2)
							{
								if(count_after != count-2){ fprintf(stdout, "Error: count_after should be %d-2. It is %d\n", count, count_after);}
								if(hand_count_after != hand_count+2){ fprintf(stdout, "Error: hand_count_after should be %d+2. It is %d\n", hand_count, hand_count_after);}
							}
							else if (count == 1)
							{
								if (count_after != 0){ fprintf(stdout, "Error: count_after should be %d-1. It is %d\n", count, count_after);}
								if(hand_count_after != hand_count+1){ fprintf(stdout, "Error: hand_count_after should be %d+1. It is %d\n", hand_count, hand_count_after);}
							}

							else if (count == 0)
							{
								if (count_after != 0){ fprintf(stdout, "Error: count_after should be 0. It is %d\n", count, count_after);}
								if(hand_count_after != hand_count){ fprintf(stdout, "Error: hand_count_after should be %d. It is %d\n", hand_count, hand_count_after);}
							}

						}

					case 1:
						{
							// play the top card in the hand, and assume it operates correctly.
							// We are testing adventurer, not the other cards.
							cardEffect(state.hand[player][0], 1, 1, 1, &state, 0, 0);
						}
				}
			}
		}

	}

	printf("Tests Complete\n");

	return 0;
}
