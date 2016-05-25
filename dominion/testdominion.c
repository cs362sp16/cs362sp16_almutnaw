#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_TESTS 50


#define VERBOSE 0

char *cardName(int card)
{
	switch(card){
		case curse: return "curse";
		case estate: return "estate";
		case duchy: return "duchy";
		case province: return "province";
		case copper: return "copper";
		case silver: return "silver";
		case gold: return "gold";
		case adventurer: return "adventurer";
		case council_room: return "council_room";
		case feast: return "feast";
		case gardens: return "gardens";
		case mine: return "mine";
		case remodel: return "remodel";
		case smithy: return "smithy";
		case village: return "village";
		case baron: return "baron";
		case great_hall: return "great_hall";
		case minion: return "minion";
		case steward: return "steward";
		case tribute: return "tribute";
		case ambassador: return "ambassador";
		case cutpurse: return "cutpurse";
		case embargo: return "embargo";
		case outpost: return "outpost";
		case salvager: return "salvager";
		case sea_hag: return "sea_hag";
		case treasure_map: return "treasure_map";
	}
}


void BuyPhase(struct gameState *G, FILE *gr_out)
{
	int ret;
	int money;
	
	while (G->numBuys > 0)
	{
		money = G->coins;
		
		ret = -1;
		/* This defines an arbitrary heirarchy of what to buy, eg buy try to buy province before anything else */
		if (money >= 8) { ret = buyCard(province, G);}
		if (money >= 6 && ret == -1) { ret = buyCard(adventurer, G); fprintf(gr_out, "Buy adventurer with status %d\n", ret); }
		if (money >= 4 && ret == -1) { ret = buyCard(gold, G); fprintf(gr_out, "Buy gold with status %d\n", ret);}
		if (money >= 5 && ret == -1) { ret = buyCard(duchy, G); fprintf(gr_out, "Buy duchy with status %d\n", ret);}
		if (money >= 3 && ret == -1) { ret = buyCard(village, G); fprintf(gr_out, "Buy village with status %d\n", ret);}
		if (money >= 3 && ret == -1) { ret = buyCard(smithy, G); fprintf(gr_out, "Buy smithy with status %d\n", ret);}
		if (money >= 3 && ret == -1) { ret = buyCard(silver, G); fprintf(gr_out, "Buy silver with status %d\n", ret);}
		if (money >= 2 && ret == -1) { ret = buyCard(estate, G); fprintf(gr_out, "Buy estate with status %d\n", ret);}
		if (money >= 5 && ret == -1) { ret = buyCard(council_room, G); fprintf(gr_out, "Buy council_room with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(feast, G); fprintf(gr_out, "Buy feast with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(gardens, G); fprintf(gr_out, "Buy gardens with status %d\n", ret);}
		if (money >= 5 && ret == -1) { ret = buyCard(mine, G); fprintf(gr_out, "Buy mine with status %d\n", ret);}
		if (money >= 0 && ret == -1) { ret = buyCard(copper, G); fprintf(gr_out, "Buy copper with status%d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(remodel, G); fprintf(gr_out, "Buy remodel with status %d\n", ret);}
		if (money >= 5 && ret == -1) { ret = buyCard(minion, G); fprintf(gr_out, "Buy minion with status %d\n", ret);}
		if (money >= 3 && ret == -1) { ret = buyCard(steward, G); fprintf(gr_out, "Buy steward with status %d\n", ret);}
		if (money >= 5 && ret == -1) { ret = buyCard(tribute, G); fprintf(gr_out, "Buy tribute with status %d\n", ret);}
		if (money >= 3 && ret == -1) { ret = buyCard(ambassador, G); fprintf(gr_out, "Buy ambassador with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(cutpurse, G); fprintf(gr_out, "Buy cutpurse with status %d\n", ret);}
		if (money >= 2 && ret == -1) { ret = buyCard(embargo, G); fprintf(gr_out, "Buy embargo with status %d\n", ret);}
		if (money >= 5 && ret == -1) { ret = buyCard(outpost, G); fprintf(gr_out, "Buy outpost with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(salvager, G); fprintf(gr_out, "Buy salvager with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(sea_hag, G); fprintf(gr_out, "Buy sea_hag with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(treasure_map, G); fprintf(gr_out, "Buy treasure_map with status %d\n", ret);}
		if (money >= 3 && ret == -1) { ret = buyCard(great_hall, G); fprintf(gr_out, "Buy great_hall with status %d\n", ret);}
		if (money >= 4 && ret == -1) { ret = buyCard(baron, G); fprintf(gr_out, "Buy baron with status %d\n", ret);}
		if (ret == -1) { ret = buyCard(copper, G); fprintf(gr_out, "Buy copper with status %d\n", ret);}
		if (ret == -1) { break; } // cant buy copper, so give up buying anything
	}
}


void print_game_state(struct gameState *G, FILE *gr_out)
{
	int i, j;
	fprintf(gr_out, "\t***************** Begin State Summary ******************\n");
	fprintf(gr_out, "\t================== State ================\n");
	fprintf(gr_out, "\t * numPlayers: %d\n", G->numPlayers);
	
	fprintf(gr_out, "\t * supplyCount:\n\t[");
	for (i = 0; i < treasure_map; i++)
	{
		fprintf(gr_out, "%d, ", G->supplyCount[i]);
	}
	fprintf(gr_out, "%d]\n", G->supplyCount[i]);

	fprintf(gr_out, "\t * embargoTokens:\n\t[");
	for (i = 0; i < treasure_map; i++)
	{
		fprintf(gr_out, "%d, ", G->embargoTokens[i]);
	}
	fprintf(gr_out, "%d]\n", G->embargoTokens[i]);

	fprintf(gr_out, "\t * outpostPlayed: %d\n", G->outpostPlayed);
	fprintf(gr_out, "\t * outpostTurn: %d\n", G->outpostTurn);
	fprintf(gr_out, "\t * whoseTurn: %d\n", G->whoseTurn);
	fprintf(gr_out, "\t * phase: %d\n", G->phase);
	fprintf(gr_out, "\t * numActions: %d\n", G->numActions);
	fprintf(gr_out, "\t * coins: %d\n", G->coins);
	fprintf(gr_out, "\t * numBuys: %d\n", G->numBuys);

	fprintf(gr_out, "\t================= Hands =================\n");
	for (i = 0; i < G->numPlayers; i++)
	{
		fprintf(gr_out, "\tPlayer %d hand count: %d\n", i+1, G->handCount[i]);
		fprintf(gr_out, "\t * [");
		for (j = 0; j < G->handCount[i]-1; j++)
		{
			fprintf(gr_out, "%d, ", G->hand[i][j]);
		}
		fprintf(gr_out, "%d]\n", G->hand[i][j]);
	}
	fprintf(gr_out, "\t================= Decks =================\n");
	for (i = 0; i < G->numPlayers; i++)
	{
		fprintf(gr_out, "\tPlayer %d deck count: %d\n", i+1, G->deckCount[i]);
		fprintf(gr_out, "\t * [");
		for (j = 0; j < G->deckCount[i]-1; j++)
		{
			fprintf(gr_out, "%d, ", G->deck[i][j]);
		}
			fprintf(gr_out, "%d]\n", G->hand[i][j]);
	}
	fprintf(gr_out, "\t*************** End State Summary ***************\n");
}


void run_turn(struct gameState *G, FILE* gr_out, int *k)
{
	int i = 0;
	int money = 0;
	int ret = 0;
	int numAdventurerers = 0;
	int adventurer_i = -1;
	int smithy_i = -1;
	int village_i = -1;

	// Hand surveying phase 
	while(i<numHandCards(G))
	{
		if (handCard(i, G) == copper){
			playCard(i, -1, -1, -1, G);
		}
		else if (handCard(i, G) == silver){
			playCard(i, -1, -1, -1, G);
		}
		else if (handCard(i, G) == gold){
			playCard(i, -1, -1, -1, G);
		}
		else if (handCard(i, G) == adventurer){
			adventurer_i = i;
		}
		else if (handCard(i, G) == smithy){
			smithy_i = i;
		}
		else if (handCard(i, G) == village){
			village_i = i;
		}
		i++;
	}

	// Action Phase 
	while (G->numActions != 0)
	{
		if (village_i >= 0 && smithy_i >= 0)
		{
			fprintf(gr_out,"Playing village and smithy\n");
			ret = playCard(village_i, -1, -1, -1, G);
			if (ret != -1)
				ret = playCard(smithy_i, -1, -1, -1, G);
		}
		else if(village_i >= 0)
		{
			fprintf(gr_out,"playing village\n");
			ret = playCard(village_i, -1, -1, -1, G);
		}
		else if(smithy_i >= 0)
		{
			fprintf(gr_out,"playing smithy\n");
			ret = playCard(smithy_i, -1, -1, -1, G);
		}
		else if (adventurer_i >= 0) 
		{
			fprintf(gr_out,"playing adventurer\n");
			ret = playCard(adventurer_i, -1, -1, -1, G);
		}
		else
		{
			ret = -1; // set to -1 incase we have no playable card in the hand, so the next if statement will trigger
			for (i = 0; i < numHandCards(G); i++)
			{
				if (handCard(i, G) > 6)
				{
					int t = handCard(i, G);
					/* Setup the choices in case you draw a card that requires them */
					int choice1 = -1, choice2 = -1, choice3 = -1;
					switch(t)
					{
						case feast:
							choice1 = k[(int)Random() * 10];
							break;
						case mine:
							for (int j = 0; j < numHandCards(G); j++)
							{
								if (handCard(j,G) == copper || handCard(j,G) == silver)
								{
									choice1 = j;
									choice2 = handCard(j, G) + 1;
									break;
								}
							}
							break;
						case remodel:
							choice1 = i ? 0:1; // If the card is in the 0 slot, trash slot 1. Else, trash slot 0
							choice2 = village; // Lets arbitrarilly buy villages!
							break;
						case baron:
							choice1 = 0; // Don't discard estates
							break;
						case minion:
							choice1 = 1; // +2 coins
							break;
						case steward:
							/* Authority is not given to you to deny the return of the King, Steward! */
							choice1 = 3; // Trash 2 cards, like Denethor trashed Gondor
							break;
						case ambassador:
							choice1 = i ? 0:1; //see remodel
							choice2 = 1; // Only deal with returning 1 to the supply
							break;
						case embargo:
							choice1 = i ? 0:1; //see remodel, it doesnt make sense to put an embargo on the embargo pile...
							break;
						case salvager:
							choice1 = i ? 0:1; // see remodel
							break;
					}
					ret = playCard(i, choice1, choice2, choice3, G);
					fprintf(gr_out, "Played %s with choices [%d, %d, %d] and result %d\n", cardName(i), choice1, choice2, choice3, ret);
				}
			}
		}
		if (ret == -1)
		{
			break;
		}
	}

	BuyPhase(G, gr_out);

	endTurn(G);
}



int main(int argc, char **argv)
{
	int i, j;
	int seed = 5;
	int test;
	int k[10];
	int num_players;
	int players[MAX_PLAYERS];
	FILE *gr_out = fopen("gameResults.out", "w");

	if (argc == 1)
	{
		printf("No seed provided. Using arbitrary default of 5\n");
	}
	else {
		seed = atoi(argv[1]);
	}

	struct gameState *G;

	for (test = 0; test < NUM_TESTS; test++)
	{
		printf ("STARTING TEST %d\n", test);

		G = newGame();

		// Reliably seed the random number generator to generate players and kingdom card sets 
		PutSeed(seed+test);

		// Randomly pick a number of players 
		double temp = Random();

		// Terrible hack to get the output of Random() into a usable range
		if (temp < .1)
			temp *= 10000;

		//printf("temp: %f\n", temp);
		num_players = (int)(temp)%3 + 2;


		/* Randomly generate k for all the games */
		for (i=0; i < 10; i++)
		{
			/* Generate a number from 7 to 26, inclusive. */
			temp = Random()*20;
			//printf("temp 2: %f\n", temp);
			k[i] = temp + 6;
			for (j = 0; j < i; j++)
			{
				if (k[i] == k[j])
				{
					// card is a duplicate, don't add to deck
					--i;
				}
			}
		}

		fprintf(gr_out," num_players: %d\n", num_players);
		fprintf(gr_out," k:");
		for (i = 0; i < 10; i++)
		{
			fprintf(gr_out," %d ", k[i]);
		}
		fprintf(gr_out,"\n");

		int ret = initializeGame(2, k, (seed+test), G);
		if (ret == -1)
			printf("ERROR INITIALIZING GAME!!!\n");

		
		while (!isGameOver(G))
		{
			int player = G->whoseTurn+1;
			fprintf(gr_out, "============== BEGIN PLAYER %d TURN ============== \n", player);
			run_turn(G, gr_out, k);

			fprintf(gr_out, "==============  END PLAYER %d TURN  ============== \n", player);
			if (VERBOSE)
				print_game_state(G, gr_out);

		}

		getWinners(players, G);
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			if (players[i] == 1)
			{
				fprintf(gr_out, "Player %d wins!\n", i+1);
			}
		}

		free(G);

	}
	return 0;
}
