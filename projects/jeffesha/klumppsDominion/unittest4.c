#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int totalTests = 28;
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
    int i;
    int cost;

    printf("\n-------------------TESTING getCost-------------------\n");

	for (i = curse; i <= treasure_map; i++) {
        cost = getCost(i);
        if(i == curse)
            myAssert(cost == 0, "Curse Costs 0");
        if(i == estate)
            myAssert(cost == 2, "Estate Costs 2");
        if(i == duchy)
            myAssert(cost == 5, "Duchy Costs 5");
        if(i == province)
            myAssert(cost == 8, "Province Costs 8");
        if(i == copper)
            myAssert(cost == 0, "Copper Costs 0");
        if(i == silver)
            myAssert(cost == 3, "Silver Costs 3");
        if(i == gold)
            myAssert(cost == 6, "Gold Costs 6");
        if(i == adventurer)
            myAssert(cost == 6, "Adventurer Costs 6");
        if(i == council_room)
            myAssert(cost == 5, "Council Room Costs 5");
        if(i == feast)
            myAssert(cost == 4, "Feast Costs 4");
        if(i == gardens)
            myAssert(cost == 4, "Gardens Costs 4");
        if(i == mine)
            myAssert(cost == 5, "Mine Costs 5");
        if(i == remodel)
            myAssert(cost == 4, "Remodel Costs 4");
        if(i == smithy)
            myAssert(cost == 4, "Smithy Costs 4");
        if(i == village)
            myAssert(cost == 3, "Village Costs 3");
        if(i == baron)
            myAssert(cost == 4, "Baron Costs 4");
        if(i == great_hall)
            myAssert(cost == 3, "Great Hall Costs 3");
        if(i == minion)
            myAssert(cost == 5, "Minion Costs 5");
        if(i == steward)
            myAssert(cost == 3, "Steward Costs 3");
        if(i == tribute)
            myAssert(cost == 5, "Tribute Costs 5");
        if(i == ambassador)
            myAssert(cost == 3, "Ambassador Costs 3");
        if(i == cutpurse)
            myAssert(cost == 4, "Cutpurse Costs 4");
        if(i == embargo)
            myAssert(cost == 2, "Embargo Costs 2");
        if(i == outpost)
            myAssert(cost == 5, "Outpost Costs 5");
        if(i == salvager)
            myAssert(cost == 4, "Salvager Costs 4");
        if(i == sea_hag)
            myAssert(cost == 4, "Sea Hag Costs 4");
        if(i == treasure_map)
            myAssert(cost == 4, "Treasure Map Costs 4");
    }

    //check return of wrong card
    cost = getCost(30);
    myAssert(cost == -1, "Test return of Invalid card");

    if(totalTests == testsPassed){
        printf("\n----------------------ALL TESTS PASSED----------------------\n");
    }
    else{
        printf("\n----------------------%d of %d TESTS PASSED----------------------\n", testsPassed, totalTests);
    }
	return 0;
}