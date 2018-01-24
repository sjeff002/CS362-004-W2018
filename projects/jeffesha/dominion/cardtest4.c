#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 11;
int testsPassed = 0;

void myAssert(int truth, char *test){
    if (truth){
        printf("TEST: %s Completed Successfully\n", test);
        testsPassed++;
    }
    else{
        printf("TEST: %s Faild!!\n", test);
    }
}


int main(){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player, player2;
    struct gameState preState, testState;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy, council_room};
    
    initializeGame(numPlayers, k, seed, &preState);
    
    printf("\n----------------------TESTING CARD council_room----------------------\n");
    
    preState.hand[player][0] = council_room;
    memcpy(&preState, &testState, sizeof(struct gameState));
    
    
    cardEffect(council_room, choice1, choice2, choice3, &testState, handpos, &bonus);
    player = whoseTurn(testState)
    
    //Should gain 4 cards, but lose 1 when smithy is discarded for a gain of 3.
    myAssert(preState.handCount[player] +3 == testState.handCount[player], "Net gain of +3 cards");
    
    //insures cards come from the players hand
    myAssert(preState.deckCount[player] -4 == testState.deckCount[player], "Cards came from players hand");
    
    // insure a card was played/discarded
    myAssert(preState.playedCardCount[player] +1 == testState.playedCardCount[player], "council_room was discarded");
    
    //insure the council_room card was played
    myAssert(testState.playedCards[testState.playedCardcount -1] == council_room, "council_room card was played");
    
    //ensure provice VC hasn't changed
    myAssert(preState.supplyCount[province] == testState.supplyCount[province], "No change in province cards");
    
    //ensure the buys increases by 1
    myAssert(preState.numBuys +1 == testState.numBuys, "Buys increased by 1");
    
    //ensure duchy VC hasn't change
    myAssert(preState.supplyCount[duchy] == testState.supplyCount[duchy], "No change in duchy cards");
    
    //ensure estate VC hasn't changed
    myAssert(preState.supplyCount[estate] == testState.supplyCount[estate], "No change in estate cards");
    
    //ensure it is still the current players turn
    myAssert(whoseTurn(testState) == whoseTurn(preState), "Turn has not changed");
    
    if(player){
        player2 = 0;
    }
    else{
        player2 = 1;
    }
    
    //make sure the other players hand increases by 1
    myAssert(preState.handCount[player2] +1 == testState.handCount[player2], "Other players hand count increases by 1");
    
    //insures card came from the other players hand
    myAssert(preState.deckCount[player] -1 == testState.deckCount[player], "Card came from other players hand");
    
    if(totalTests == testsPassed){
        printf("\n----------------------ALL TESTS PASSED----------------------\n");
    }
    else{
        printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
    }
}