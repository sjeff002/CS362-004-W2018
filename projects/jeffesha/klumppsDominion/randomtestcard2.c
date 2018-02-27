/***************************************************************************
*Author: Shannon Jeffers
*Class: CS362
*Assignment 4
*File: randomtestcard2.c
***************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sameDeck = 0, sameDeckTotal = 0;
int cardsDrawn = 0, cardsDrawnTotal = 0;
int oneHand = 0, oneHandTotal = 0;
int turn = 0, turnTotal = 0;
int cardCount = 0, cardCountTotal = 0;
int cardPlayed = 0, cardPlayedTotal = 0;
int provenceC = 0, provenceCTotal = 0;
int duchyC = 0, duchyCTotal = 0;
int estateC = 0, estateCTotal = 0;
int actions = 0, actionsTotal = 0;

void myAssert(int truth, char *test, int *testVar, int *testTotal){
	*testTotal += 1;
	if (truth) {
		printf("TEST: %s Completed Successfully.\n", test);
		*testVar += 1;
	}
	else
		printf("TEST: %s Failed.\n", test);
}

int checkCards(int k[10], int card){
	int i;
	for(i = 0; i < 10; i++){
		if(k[i] == card)
			return 1;
	}
	return 0;
}


int main() {
	srand(time(NULL));
	int i, z;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed;
	int temp;
	int numPlayers;
	int player =0, player2;
	struct gameState preState, testState;
	int k[10];

	printf("\n----------------------TESTING CARD village----------------------\n");
	
	for(i = 0; i < 200; i++){
		printf("Test iteration %d\n", i+1);
		
		numPlayers = rand() % 3 + 2; //need 2-4 players
		player = rand() % numPlayers;
		seed = rand();
		//set up the game
		z=0;
		while(z != 9){
			temp = rand() % treasure_map + adventurer;
			if(!checkCards(k, temp)){
				k[z] = temp;
				z++;
			}
		}
		
		initializeGame(numPlayers, k, seed, &preState);
		
		preState.handCount[player] = rand() % MAX_HAND-1;
		preState.discardCount[player] = rand() % MAX_DECK-1;
		preState.deckCount[player] = rand() % MAX_DECK-1;
		if (preState.handCount[player])
			handpos = rand() % preState.handCount[player];
		else
			handpos = 0;
		preState.hand[player][handpos] = village;
		preState.whoseTurn = player;

		memcpy(&testState, &preState, sizeof(struct gameState));
	
		cardEffect(village, choice1, choice2, choice3, &testState, handpos, &bonus);
	
		//Should gain 1 cards, but lose 1 when village is discarded for a gain of 0.
		myAssert(preState.handCount[player] == testState.handCount[player], "Net gain of +0 cards", &cardsDrawn, &cardsDrawnTotal);
	
		//insures cards come from the players hand
		myAssert(preState.deckCount[player] - 1 == testState.deckCount[player], "Cards came from players hand", &sameDeck, &sameDeckTotal);
	
		//actions should increase by 2 because subtracting the current action is done by a different function
		myAssert(preState.numActions + 2 == testState.numActions, "Actions increase by 2", &actions, &actionsTotal);
	
		// insure a card was played/discarded
		myAssert(preState.playedCardCount + 1 == testState.playedCardCount, "village was discarded", &cardCount, &cardCountTotal);

		//insure the smithy card was played
		myAssert(testState.playedCards[testState.playedCardCount - 1] == village, "village card was played", &cardPlayed, &cardPlayedTotal);
	
		//ensure provice VC hasn't changed
		myAssert(preState.supplyCount[province] == testState.supplyCount[province], "No change in province cards", &provenceC, &provenceCTotal);
	
		//ensure duchy VC hasn't change
		myAssert(preState.supplyCount[duchy] == testState.supplyCount[duchy], "No change in duchy cards", &duchyC, &duchyCTotal);
	
		//ensure estate VC hasn't changed
		myAssert(preState.supplyCount[estate] == testState.supplyCount[estate], "No change in estate cards", &estateC, &estateCTotal);
	
		//ensure it is still the current players turn
		myAssert(whoseTurn(&testState) == whoseTurn(&preState), "Turn has not changed", &turn, &turnTotal);

		if(player != numPlayers-1){
			player2 = player + 1;
		}
		else{
			player2 = 0;
		}
	
		//make sure there is no change to the other player hand
		myAssert(preState.handCount[player2] == testState.handCount[player2], "Other players hand count is the same", &oneHand, &oneHandTotal);
        printf("\n\n");

	}
	printf("Cards came from players deck passed %d of %d times\n", sameDeck, sameDeckTotal);
	printf("Hand count increased by 1 passed %d of %d times\n", cardsDrawn, cardsDrawnTotal);
	printf("Action count increased by 1 passed %d of %d times\n", actions, actionsTotal);
	printf("Second player hand did not change passed %d of %d times\n", oneHand, oneHandTotal);
	printf("Turn did not change passed %d of %d times\n", turn, turnTotal);
	printf("Played cards increased by 1 passed %d of %d times\n", cardCount, cardCountTotal);
	printf("adventurer card was played passed %d of %d times\n", cardPlayed, cardPlayedTotal);
	printf("No change in province cards passed %d of %d times\n", provenceC, provenceCTotal);
	printf("No change in duchy cards passed %d of %d times\n", duchyC, duchyCTotal);
	printf("No change in estate cards passed %d of %d times\n\n", estateC, estateCTotal);
	
	return 0;
}