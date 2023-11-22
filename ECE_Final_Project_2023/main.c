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
    struct card_s* next; //card.next... this is a pointer to an address of type card.

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
        printf("%d", thisCard->face);
        printf(SPADE);
        printf("\n");
    }
    else if (thisCard->suit == 'h') {
        printf("%d", thisCard->face);
        printf(HEART);
        printf("\n");
    }
    else if (thisCard->suit == 'c') {
        printf("%d", thisCard->face);
        printf(CLUB);
        printf("\n");
    }

    else if (thisCard->suit == 'd') {
        printf("%d", thisCard->face);
        printf(DIAMOND);
        printf("\n");
    }
    else {
        printf("\n");
    }

}

// Grab location pointed by nextNodePtr
card* CardNode_GetNext(card* thisCard) {
    return thisCard->next;
}

void swapCards(card* deck_head, int pos1, int pos2) {

    int temp;
}

void shuffleCards(card* deck_head, card* currObj, int num_cards) //Fisher-Yates shuffle algorithm
{
    srand((int)time(0));
    currObj = deck_head;
    card* prevObj1, * prevObj2, * card1_swap, * card2_swap;
    prevObj1 = NULL;
    prevObj2 = NULL;


    for (int i = 0; i < 100; i++)
    {
        for (int j = 2; j < num_cards - 1; j++)
        {
            int pos1 = j;
            int pos2 = rand() % 37;
            int count = 1;

            if (pos1 == pos2) //without this, you will sometimes have compilation errors.
            {
                continue; //if same do nothing.
            }
            else if (pos2 == 1 || pos2 == 0) //dont bother cant read it 
            {
                continue;
            }

            if (pos1 != pos2 && pos2 != 1)
            {
                while (currObj != NULL && count <= num_cards)
                {
                    if (count == pos1 - 1) {
                        prevObj1 = currObj;
                    }
                    if (count == pos1) {
                        card1_swap = currObj;
                    }
                    if (count == pos2 - 1) {
                        prevObj2 = currObj;
                    }
                    if (count == pos2) {
                        card2_swap = currObj;
                    }
                    currObj = currObj->next;
                    count++;
                }

                if (card1_swap != NULL && card2_swap != NULL)
                {
                    prevObj1->next = card2_swap;
                    prevObj2->next = card1_swap;

                    currObj = card1_swap->next;
                    card1_swap->next = card2_swap->next;
                    card2_swap->next = currObj;

                    if (prevObj1 == NULL) //compile errors without this.
                    {
                        deck_head = card2_swap;
                    }
                    else if (prevObj1 == NULL)
                    {
                        deck_head = card1_swap;
                    }
                }



            }




        }
    }

}

void testUnicode() { //just a test for unicode characters. works on mac.

    printf(SPADE);
    printf(CLUB);
    printf(DIAMOND);
    printf(HEART);
    printf("\n");
}

void printDeck(card* deck_head, card* currObj) {

    //Print linked list.. deck
    currObj = deck_head;
    while (currObj != NULL) {
        CardNode_PrintNodeData(currObj);
        currObj = CardNode_GetNext(currObj);
    }
}

int main(void) {


    char player_name[100]; //may change later. names may not always be just 100 char long.
    printf("Enter your name: ");
    scanf("%s", player_name);
    printf("\n%s lets play go fish!\n", player_name);

    card* currObj = NULL;
    card* deck_head = NULL;
    card* lastObj = NULL;

    //testUnicode(); //the output of these symbols work on windows and mac!

    deck_head = (card*)malloc(sizeof(card));
    CardNode_Create(deck_head, -1, -1, NULL);
    lastObj = deck_head;

    //Generate deck of cards
    int num_cards = 0;
    for (int i = 1; i < 10; i++) //number of faces... 1 = ACE
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
            num_cards++;
        }
    }
    printf("Original deck: \n");
    printDeck(deck_head, currObj); //check to see if deck formed correctly.
    shuffleCards(deck_head, currObj, num_cards);
    printf("\nShuffled deck: \n");
    printDeck(deck_head, currObj); //check shuffled deck

    free(deck_head);
    return 0;
}



