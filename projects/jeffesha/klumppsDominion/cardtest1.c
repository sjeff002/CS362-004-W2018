/************************************************
* Author: Shannon Jeffers
* Class: CS362
* Assignment 3
* File: cardtest1.c
************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 6;
int passedTests = 0;

void myAssert(int truth, char *test){
	if (truth) {
		printf("TEST: %s Completed Successfully.\n", test);
		passedTests++;
	}
	else
		printf("TEST: %s Failed.\n", test);
}


int main(){

	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int player = 0;
	int player2 = 1;
	struct gameState preState, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	//set up the game
	initializeGame(numPlayers, k, seed, &preState);

	printf("\n-------------------TESTING Card: adventurer-------------------\n");

	//make a copy of game state
	memcpy(&testState, &preState, sizeof(struct gameState));

	//play the card
	cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);

	player = whoseTurn(&testState);
	//counters to keep track of treasure in players hand
	int testTreasure = 0, origTreasure = 0;

	//Make sure cards came from the players deck
	myAssert(testState.deckCount[player] < preState.deckCount[player], "Cards came from players deck");

	//make sure 2 cards were drawn. Should increase by 1 due to discard.
	myAssert(testState.handCount[player]-1 == preState.handCount[player], "Hand count increased by 1");

	//count up the treasure in both hands
	for(i=0; i < testState.handCount[player]; i++){
		if(testState.hand[player][i] == copper || silver || gold){
			testTreasure++;
		}
	}
	for(i=0; i < preState.handCount[player]; i++){
		if(preState.hand[player][i] == copper || silver || gold){
			origTreasure++;
		}
	}

	//trasure should have increased by 2
	myAssert(testTreasure == origTreasure +2, "Treasure count increased by 2");

	if(!whoseTurn(&testState))
		player2 = 1;
	else
		player2 = 0;

	//ensures only one players hand is effected
	myAssert(preState.handCount[player2] == testState.handCount[player2], "Second player hand did not change.");

	//checks it is still the same players turn
	myAssert(whoseTurn(&preState) == whoseTurn(&testState), "Turn did not change");

	//checks played card count increases by one
	myAssert(testState.playedCardCount == preState.playedCardCount + 1, "Played cards increased by 1");

	if (passedTests == 6)
		printf("\n-------------------ALL TESTS PASS-------------------\n");
	
	else
		printf("\n-------------------%d of %d TESTS PASSED-------------------\n", passedTests, totalTests);
	return 0;
}