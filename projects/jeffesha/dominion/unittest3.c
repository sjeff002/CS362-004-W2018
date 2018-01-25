#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 3;
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
    int over;
    int seed = 1000;
    int numPlayers = 2;
    struct gameState state, test;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy, council_room};
    
    initializeGame(numPlayers, k, seed, &state);
    
    printf("\n-------------------TESTING isGameOver-------------------\n");

    memcpy(&test, &state, sizeof(struct gameState));

    over = isGameOver(&test);
    //game is not over. Province and supply piles are full
    myAssert(over == 0, "The game is not over");

    test.supplyCount[province] = 0;

    over = isGameOver(&test);
    //ensures the game ends when province is empty
    myAssert(over == 1, "Province pile empty, game is over");

    //reset piles
    memcpy(&state, &test, sizeof(struct gameState));

    test.supplyCount[gold] = 0;
    test.supplyCount[duchy] = 0;
    test.supplyCount[silver] = 0;
    over = isGameOver(&test);
    //ensures game ends when 3 supply piles are empty.
    myAssert(over = 1, "3 supply piles are empty, game is over");

    if(totalTests == testsPassed){
        printf("\n----------------------ALL TESTS PASSED----------------------\n");
    }
    else{
        printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
    }
	return 0;
}