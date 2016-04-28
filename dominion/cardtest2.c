
#include"dominion.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	struct gameState G;
	struct gameState *p = &G;
	int num = 1;
	int *ponus = &num;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	  
  	initializeGame(2, k, atoi(argv[1]), p);	
  	
  	

  	myAssert((cardEffect(k[3], 1, 1, 1, p, 0, ponus) == 0), "Problem with adventurer card");

	return 0;

}
