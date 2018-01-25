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
    int i, count;
    int bonus = 12;
    int seed = 1000;
    int numPlayers = 2;
    int player =0;
    struct gameState state, test;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy, council_room};
    
    initializeGame(numPlayers, k, seed, &state);
    
    printf("\n-------------------TESTING updateCoins-------------------\n");

    memcpy(&test, &state, sizeof(struct gameState));


    //test with no treasure in hand.
    for(i=0; i < 5; i++){
        test.hand[player][i] = smithy;
		test.handCount[player]++;
    }
    count = updateCoins(player, &test, 0);
    myAssert(count == 0, "There are no coins in hand");

    //revert to default memory
    memcpy(&test, &state, sizeof(struct gameState));
    //test with all copper
	for (i = 0; i < 5; i++) {
        test.hand[player][i] = copper;
		test.handCount[player]++;
    }
    count = updateCoins(player, &test, 0);
    myAssert(count == 5, "There are 5 coins in hand");

    //revert to default memory
    memcpy(&test, &state, sizeof(struct gameState));
    //test with all silver
	for (i = 0; i < 5; i++) {
        test.hand[player][i] = silver;
		test.handCount[player]++;
    }
    count = updateCoins(player, &test, 0);
    myAssert(count == 10, "There are 10 coins in hand");

    //revert to default memory
    memcpy(&test, &state, sizeof(struct gameState));
    //test with all gold
	for (i = 0; i < 5; i++) {
        test.hand[player][i] = gold;
		test.handCount[player]++;
    }
    count = updateCoins(player, &test, 0);
    myAssert(count == 15, "There are 15 coins in hand");

    //revert to default memory
    memcpy(&test, &state, sizeof(struct gameState));
    //test with mixture
	test.handCount[player] = 5;
    test.hand[player][0] = copper;
    test.hand[player][1] = silver;
    test.hand[player][2] = gold;
    test.hand[player][3] = silver;
    test.hand[player][4] = copper;
	count = updateCoins(player, &test, 0);
    myAssert(count == 9, "There are 9 coins in hand");

    //revert to default memory
    memcpy(&test, &state, sizeof(struct gameState));
    //test with mixed coins and bonus
	test.handCount[player] = 5;
    test.hand[player][0] = copper;
    test.hand[player][1] = silver;
    test.hand[player][2] = gold;
    test.hand[player][3] = silver;
    test.hand[player][4] = copper;
	count = updateCoins(player, &test, bonus);
    myAssert(count == 21, "There are 9 coins and 12 bonus for a total of 21 coins");

    if(totalTests == testsPassed){
        printf("\n----------------------ALL TESTS PASSED----------------------\n");
    }
    else{
        printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
    }

	return 0;
}