// CMakeProject_Khalil.c : Defines the entry point for the application.
//
// See final_project_notes.txt in the repo for the pseudocode.


#include "CMakeProject_Khalil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

#if defined(_WIN32) || defined(__MSDOS__) //for unicode definitions. need to test on windows.
#define SPADE   "\x06"
#define CLUB    "\x05"
#define HEART   "\x03"
#define DIAMOND "\x04"
#else
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#endif



typedef struct card_s {			//can add or change to this but not delete any preexisting

    char suit; //s - spade, h - heart, d - diamond, c - club
    int face;
    struct card_s* next;

} card;

void CardNode_Create(card* thisCard, char suit, int face, card* nextCard) {
    thisCard->suit = suit;
    thisCard->face = face;
    thisCard->next = nextCard;

}

void CardNode_InsertAfter(card* thisCard, card* newCard) {
    card* tmpNext = NULL;

    tmpNext = thisCard->next; // Remember next
    thisCard->next = newCard; // this -- new -- ?
    newCard->next = tmpNext;  // this -- new -- next
}

void CardNode_PrintNodeData(card* thisCard) {
    
    if (thisCard->suit == 's') {
        thisCard->suit = SPADE;
        printf("%d %c\n", thisCard->face, thisCard->suit);
    }
    else if (thisCard->suit == 'h') {
        thisCard->suit = CLUB; 
        printf("%d %c\n", thisCard->face, thisCard->suit);
    }
    else if (thisCard->suit== 'c') {
        thisCard->suit = HEART;
        printf("%d %c\n", thisCard->face, thisCard->suit);
    }
    else if (thisCard -> suit == 'd') {
        thisCard->suit= DIAMOND;
        printf("%d %c\n", thisCard->face, thisCard->suit);
    }
    else {
        printf("\n");
    }
    
}

// Grab location pointed by nextNodePtr
card* IntNode_GetNext(card* thisCard) {
    return thisCard->next;
}

void Shuffle_Card()
{
    srand((int)time(0));
    printf("%d\n", rand() % 37);

    //j = 1  =>  rand() % 37 -> 10 <- move p2 from headObj 10 times
    //J = 2  =>  rand() % 37 -> 20 <- move p2 from headObj 20 times
    // set curr to head of the list
    // while (curr is not null)
    // {
    //      do something
    //      curr=curr->next //or use Node_GetNext(function)
    // }
    //"should work with any size deck of cards"
    //"[see sec 2.24 Random numbers in your zyBooks]"
    //"You should seed the random number generator with a call to time() with srand()"
}

void testUnicode() { //just a test for unicode characters. works on mac.

    printf(SPADE);
    printf(CLUB);
    printf(DIAMOND);
    printf(HEART);
    printf("\n");
}

int main(void) {


    char player_name[100]; //may change later. names may not always be just 100 char long.
    printf("Enter your name: ");
    scanf("%s", player_name);
    printf("\n%s lets play go fish!\n", player_name);

    card* currObj = NULL;
    card* deck_head = NULL;
    card* lastObj = NULL;

    testUnicode(); //the output of these symbols work on windows and mac!

    deck_head = (card*)malloc(sizeof(card));
    CardNode_Create(deck_head, -1, -1, NULL);
    lastObj = deck_head;

    for (int i = 1; i < 10; i++) //number of faces
    {
        for (int j = 0; j < 4; j++) //card suit
        {
            char temp;
            if (j == 0) {
                temp = 's';
            }
            else if (j == 1) {
                temp = 'h';
            }
            else if (j == 2) {
                temp = 'd';
            }
            else {
                temp = 'c';
            }
            currObj = (card*)malloc(sizeof(card));
            CardNode_Create(currObj, temp, i, NULL); 
            CardNode_InsertAfter(lastObj, currObj);
            lastObj = currObj;
        }
    }

    //Print linked list.. deck
    currObj = deck_head;
    while (currObj != NULL) {
        CardNode_PrintNodeData(currObj);
        currObj = IntNode_GetNext(currObj);
        
    }

    free(deck_head);
    return 0;
}





