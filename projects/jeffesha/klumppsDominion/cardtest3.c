/***************************************************************************
*Author: Shannon Jeffers
*Class: CS362
*Assignment 3
*File: cardtest3
***************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 10;
int testsPassed = 0;

void myAssert(int truth, char *test){
    if (truth){
        printf("TEST: %s Completed Successfully\n", test);
        testsPassed++;
    }
    else{
        printf("TEST: %s Failed!!\n", test);
    }
}


int main() {
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int player =0, player2;
	struct gameState preState, testState;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, seed, &preState);

	printf("\n----------------------TESTING CARD village----------------------\n");

	preState.hand[player][0] = village;
	memcpy(&testState, &preState, sizeof(struct gameState));

	cardEffect(village, choice1, choice2, choice3, &testState, handpos, &bonus);
	player = whoseTurn(&testState);

	//Should gain 1 cards, but lose 1 when village is discarded for a gain of 0.
	myAssert(preState.handCount[player] == testState.handCount[player], "Net gain of +0 cards");

	//insures cards come from the players hand
	myAssert(preState.deckCount[player] - 1 == testState.deckCount[player], "Cards came from players hand");

	//actions should increase by 2 because subtracting the current action is done by a different function
	myAssert(preState.numActions + 2 == testState.numActions, "Actions increase by 2");

	// insure a card was played/discarded
	myAssert(preState.playedCardCount + 1 == testState.playedCardCount, "village was discarded");

	//insure the smithy card was played
	myAssert(testState.playedCards[testState.playedCardCount - 1] == village, "village card was played");

	//ensure provice VC hasn't changed
	myAssert(preState.supplyCount[province] == testState.supplyCount[province], "No change in province cards");

	//ensure duchy VC hasn't change
	myAssert(preState.supplyCount[duchy] == testState.supplyCount[duchy], "No change in duchy cards");

	//ensure estate VC hasn't changed
	myAssert(preState.supplyCount[estate] == testState.supplyCount[estate], "No change in estate cards");

	//ensure it is still the current players turn
	myAssert(whoseTurn(&testState) == whoseTurn(&preState), "Turn has not changed");

	if (player) {
		player2 = 0;
	}
	else {
		player2 = 1;
	}

	//make sure there is no change to the other player hand
	myAssert(preState.handCount[player2] == testState.handCount[player2], "Other players hand count is the same");

	if (totalTests == testsPassed) {
		printf("\n----------------------ALL TESTS PASSED----------------------\n");
	}
	else {
		printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
	}
	return 0;
}