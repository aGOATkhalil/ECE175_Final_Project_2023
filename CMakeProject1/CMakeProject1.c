
#include "CMakeProject1.h"

    //Rayce Bacchus & Khalil Gatto
    //11-4-2023

    /*
    ***************************************************************************************************************
                        USE LINKED LISTS OR ELSE GET 0
    ***************************************************************************************************************
    */


#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


    typedef struct card_s			//can add or change to this but not delete any preexisting
    {
        char suit;
        int face;
        struct card_s* next;
    } card;

    void Shuffle_Card() {

        printf("hi");
        //"should work with any size deck of cards"
        //"[see sec 2.24 Random numbers in your zyBooks]"
        //"You should seed the random number generator with a call to time() with srand()"
    }

    int main(void) {

        //blah blah stuff blah blah
        //balls

        char player_name[100]; //may change later. names may not always be just 100 char long.

        printf("Enter your name: ");
        scanf("%s", player_name);
        printf("\n%s lets play go fish!\n", player_name);

        printf("stuff");

        return 0;
    }

