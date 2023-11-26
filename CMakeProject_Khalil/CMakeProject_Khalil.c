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
    else if (thisCard->suit== 'c') {
        printf("%d", thisCard->face);
        printf(CLUB);
        printf("\n");
    }

    else if (thisCard -> suit == 'd') {
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


void shuffleCards(card* deck_head,card* currObj, int num_cards) //Fisher-Yates shuffle algorithm
{
    srand((int)time(0));
    currObj = deck_head;
    card* temp, * prevObj1, * prevObj2;
    
    for (int i = 1; i < 1000; i++) //shuffle at least two hundred times
    {    
        for (int j = 0; j < num_cards; j++) {

            int random_index = rand() % num_cards;

            // Find the nodes to swap
            card* card1_swap = deck_head;
            card* card2_swap = deck_head;

            for (int k = 0; k < j; k++) {
                card1_swap = CardNode_GetNext(card1_swap);
            }

            for (int k = 0; k < random_index; k++) {
                card2_swap = CardNode_GetNext(card2_swap);
            }

            // Swap the values (face and suit)
            int temp_face = card1_swap->face;
            char temp_suit = card1_swap->suit;
            card1_swap->face = card2_swap->face;
            card1_swap->suit = card2_swap->suit;
            card2_swap->face = temp_face;
            card2_swap->suit = temp_suit;
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

    int deck_size = 0;

    //Print linked list.. deck
    currObj = deck_head->next;
    while (currObj != NULL) {
        CardNode_PrintNodeData(currObj);
        currObj = CardNode_GetNext(currObj);
        deck_size++;
    }
    printf("\nDeck size: %d\n", deck_size);
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
    shuffleCards(deck_head,currObj, num_cards);
    printf("\nShuffled deck: \n");
    printDeck(deck_head, currObj); //check shuffled deck

    free(deck_head);
    free(currObj);
    return 0;
}





