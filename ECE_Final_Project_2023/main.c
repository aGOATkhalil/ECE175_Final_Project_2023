//Rayce Bacchus & Khalil Gatto
//11-4-2023

/*
 
 See final_project_notes.txt in the repo for the pseudocode.
 
 */



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void Shuffle_Card(); // Shuffle cards.

typedef struct card_s			//can add or change to this but not delete any preexisting
{
    char suit;
    int face;
    struct card_s* next;
} card;

void Shuffle_Card()
{				
   //"should work with any size deck of cards"
   //"[see sec 2.24 Random numbers in your zyBooks]"
   //"You should seed the random number generator with a call to time() with srand()"



}

int main(void) {

    
    char player_name[100]; //may change later. names may not always be just 100 char long.

    printf("Enter your name: ");
    scanf("%s", player_name);
    printf("\n%s lets play go fish!\n", player_name);



    return 0;
}
