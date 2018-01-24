/***************************************************************
*Author: Shannon Jeffers
*Class: CS362
*Assignment 3
*File: cardtest2.c
****************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 8;
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


int main(){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0, player2;
    struct gameState preState, testState;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy, council_room};
    
    initializeGame(numPlayers, k, seed, &preState);
    
    printf("\n----------------------TESTING CARD smithy----------------------\n");
    
    preState.hand[player][0] = smithy;
    memcpy(&preState, &testState, sizeof(struct gameState));
    
    
    cardEffect(smithy, choice1, choice2, choice3, &testState, handpos, &bonus);
	player = whoseTurn(&testState);
    
    //Should gain 3 cards, but lose 1 when smithy is discarded for a gain of 2.
    myAssert(preState.handCount[player] +2 == testState.handCount[player], "Net gain of +2 cards");
    
    //insures cards come from the players hand
    myAssert(preState.deckCount[player] > testState.deckCount[player], "Cards came from players hand");
    
    // insure a card was played/discarded
    myAssert(preState.playedCardCount +1 == testState.playedCardCount, "smithy was discarded");
    
    //ensure provice VC hasn't changed
    myAssert(preState.supplyCount[province] == testState.supplyCount[province], "No change in province cards");
    
    //ensure duchy VC hasn't change
    myAssert(preState.supplyCount[duchy] == testState.supplyCount[duchy], "No change in duchy cards");
    
    //ensure estate VC hasn't changed
    myAssert(preState.supplyCount[estate] == testState.supplyCount[estate], "No change in estate cards");
    
    //ensure it is still the current players turn
    myAssert(whoseTurn(&testState) == whoseTurn(&preState), "Turn has not changed");
    
    if(player){
        player2 = 0;
    }
    else{
        player2 = 1;
    }
    
    //make sure there is no change to the other player hand
    myAssert(preState.handCount[player2] == testState.handCount[player2], "Other players hand count is the same");
    
    if(totalTests == testsPassed){
        printf("\n----------------------ALL TESTS PASSED----------------------\n");
    }
    else{
        printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
    }
	return 0;
}