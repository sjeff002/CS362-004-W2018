/************************************************
* Author: Shannon Jeffers
* Class: CS362
* Assignment 4
* File: randomtestadventurer.c
************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

int main(){
	srand(time(NULL));

	int sameDeck = 0, sameDeckTotal = 0;
	int cardsDrawn = 0, cardsDrawnTotal = 0;
	int treasureDif = 0, treasureDifTotal = 0;
	int oneHand = 0, oneHandTotal = 0;
	int turn = 0, turnTotal = 0;
	int cardCount = 0, cardCountTotal = 0;
	int cardPlayed = 0, cardPlayedTotal = 0;
	int provenceC = 0, provenceCTotal = 0;
	int duchyC = 0, duchyCTotal = 0;
	int estateC = 0, estateCTotal = 0;
	int discard = 0, discardTotal = 0;

	int i,j, z;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed;
	int numPlayers = 0;
	int player = 0;
	int player2;
	int temp;
	struct gameState preState, testState;
	int k[10];

	printf("\n-------------------TESTING Card: adventurer-------------------\n");

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
		preState.hand[player][handpos] = adventurer;
		preState.whoseTurn = player;

		for(z = 0; z < preState.deckCount[player]; z++){
			if(z != preState.deckCount[player]-1 && z != preState.deckCount[player]-2){
				preState.hand[player][z] = rand() % treasure_map;
			}
			else{
				preState.hand[player][z] = copper;
			}
		}
		
		//make a copy of game state
		memcpy(&testState, &preState, sizeof(struct gameState));
	
		//play the card
		cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
	
		int testTreasure = 0, origTreasure = 0;

		//Make sure cards came from the players deck
		myAssert(testState.deckCount[player] < preState.deckCount[player], "Cards came from players deck", &sameDeck, &sameDeckTotal);
	
		//make sure 2 cards were drawn. Should increase by 1 due to discard.
		myAssert(testState.handCount[player]-1 == preState.handCount[player], "Hand count increased by 1", &cardsDrawn, &cardsDrawnTotal);
	
		//count up the treasure in both hands
		for(j=0; j < testState.handCount[player]; j++){
			if(testState.hand[player][j] == copper || silver || gold){
				testTreasure++;
			}
		}
		for(j=0; j < preState.handCount[player]; j++){
			if(preState.hand[player][j] == copper || silver || gold){
				origTreasure++;
			}
		}
	
		//trasure should have increased by 2
		myAssert(testTreasure == origTreasure +2, "Treasure count increased by 2", &treasureDif, &treasureDifTotal);

		if(preState.deckCount[player] > 2){
			if(preState.deck[player][preState.deckCount[player]-1] != copper || silver || gold){
				myAssert(preState.discardCount[player] < testState.discardCount[player], "Non-Tresure's were discarded", &discard, &discardTotal);
			}
		}
	
		if(player != numPlayers-1){
			player2 = player + 1;
		}
		else{
			player2 = 0;
		}
	
		//ensures only one players hand is effected
		myAssert(preState.handCount[player2] == testState.handCount[player2], "Second player hand did not change.", &oneHand, &oneHandTotal);
	
		//checks it is still the same players turn
		myAssert(whoseTurn(&preState) == whoseTurn(&testState), "Turn did not change", &turn, &turnTotal);

		//checks played card count increases by one
		myAssert(testState.playedCardCount == preState.playedCardCount + 1, "Played cards increased by 1", &cardCount, &cardCountTotal);
		
		//insure the adventurer card was played
		if (testState.playedCardCount) {
			myAssert(testState.playedCards[testState.playedCardCount - 1] == adventurer, "adventurer card was played", &cardPlayed, &cardPlayedTotal);
		}
	    //ensure provice VC hasn't changed
	    myAssert(preState.supplyCount[province] == testState.supplyCount[province], "No change in province cards", &provenceC, &provenceCTotal);
	    
	    //ensure duchy VC hasn't change
	    myAssert(preState.supplyCount[duchy] == testState.supplyCount[duchy], "No change in duchy cards", &duchyC, &duchyCTotal);
	    
	    //ensure estate VC hasn't changed
	    myAssert(preState.supplyCount[estate] == testState.supplyCount[estate], "No change in estate cards", &estateC, &estateCTotal);
	    
		printf("\n\n");
	}
	
	printf("Cards came from players deck passed %d of %d times\n", sameDeck, sameDeckTotal);
	printf("Hand count increased by 1 passed %d of %d times\n", cardsDrawn, cardsDrawnTotal);
	printf("Treasure count increased by 2 passed %d of %d times\n", treasureDif, treasureDifTotal);
	printf("Second player hand did not change passed %d of %d times\n", oneHand, oneHandTotal);
	printf("Turn did not change passed %d of %d times\n", turn, turnTotal);
	printf("Played cards increased by 1 passed %d of %d times\n", cardCount, cardCountTotal);
	printf("adventurer card was played passed %d of %d times\n", cardPlayed, cardPlayedTotal);
	printf("No change in province cards passed %d of %d times\n", provenceC, provenceCTotal);
	printf("No change in duchy cards passed %d of %d times\n", duchyC, duchyCTotal);
	printf("No change in estate cards passed %d of %d times\n\n", estateC, estateCTotal);
	

	return 0;
}