//unittest2.c

#include"dominion.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	struct gameState G;
	struct gameState *p = &G;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	  
  	initializeGame(2, k, atoi(argv[1]), p);	



  	myAssert((whoseTurn(p)==0), "Problem with whoseTurn func");

	return 0;
}
