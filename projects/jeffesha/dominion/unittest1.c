#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 6;
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
    int seed = 1000;
    int numPlayers = 2;
    struct gameState test1, test2, test3, preTest4, test4;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy, council_room};
    
    initializeGame(numPlayers, k, seed, &test1);
    
    printf("\n-------------------TESTING buyCard-------------------\n");

    memcpy(&test2, &test1, sizeof(struct gameState));
    
    memcpy(&test3, &test1, sizeof(struct gameState));
    
    memcpy(&preTest4, &test1, sizeof(struct gameState));
    
    memcpy(&test4, &test1, sizeof(struct gameState));
    
    test1.coins = 2;
    test2.coins = 3;
    test2.numBuys = 0;
    test3.supplyCount[village] = 0;
    test4.coins = 3;
    preTest4.coins = 3;
    int returns;
    
    //ensures buyCard doesnt allow purchase without proper coin amount.
    myAssert((returns = buyCard(village, &test1)) == -1, "Fails to buy a card if not enough coins");
    
    //ensures a player cannot buy a card if they have no buys
    myAssert((returns = buyCard(village, &test2)) == -1, "Fails to buy if no buys remaining");
    
    //ensures buyCard doesn't allow purchase of unavailible cards
    myAssert((returns = buyCard(village, &test3)) == -1, "Fails to buy if there are no more of the card");
    
    //if player has a buy, the card is in stock and they have the coins they can buy it
    myAssert((returns = buyCard(village, &test4)) == 0, "Buys card successfully");
    
    //assures the buy is removed from the player
    myAssert(test4.numBuys +1 == preTest4.numBuys, "The buy has been used");
    
    //assures player doesn't keep their coins
    myAssert(test4.coins +3 == preTest4.coins, "The coins are removed from play");
    
    if(totalTests == testsPassed){
        printf("\n----------------------ALL TESTS PASSED----------------------\n");
    }
    else{
        printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
    }

	return 0;

}

