// CMakeProject_Khalil.c : Defines the entry point for the application.
//
// See final_project_notes.txt in the repo for the pseudocode.
//Test functions are below main(). Useful functions are above main().


#include "CMakeProject_Khalil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
    int face; //1 - ACE
    struct card_s* next; //card.next... this is a pointer to an address of type card.

} card;

typedef struct player_s {

    char name[100];
    card* hand;

}player;

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
    else if (thisCard -> suit == 'd') {
        printf("%d", thisCard->face);
        printf(DIAMOND);
        printf("\n");
    }
    else {
        printf("\n");
    } 
}

card* CardNode_GetNext(card* thisCard) {
    return thisCard->next;
}


void shuffleCards(card* deck_head, card* currObj, int num_cards) //Fisher-Yates shuffle algorithm
{
    srand((int)time(0));
    currObj = deck_head;
    card* temp, * prevObj1, * prevObj2;
    
    for (int i = 1; i < 1000; i++) //shuffle num times
    {    
        for (int j = 0; j < num_cards; j++) {

            int random_index = rand() % num_cards;

            // Find the nodes to swap
            card* card1_swap = deck_head->next;
            card* card2_swap = deck_head->next;

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

void printDeck(card* deck_head, card* currObj) {

    //Print linked list.. deck
    currObj = deck_head->next;
    while (currObj != NULL) {
        CardNode_PrintNodeData(currObj);
        currObj = CardNode_GetNext(currObj);
    }
}

void testUnicode(); //just a test for unicode characters. works on mac
void testGame(card* deck_head, card* currObj, int num_cards); //dev menu. number of tests in this function.

int main(void) {

    char player_name[100]; //may change later. names may not always be just 100 char long.
    player player_1; //also could change if we want extra credit. 
    player player_2;
    
    printf("Enter your name: ");
    scanf("%s", player_1.name);
    printf("\n%s lets play go fish!\n", player_1.name);

    card* currObj = NULL;
    card* deck_head = NULL;
    card* lastObj = NULL;
    deck_head = (card*)malloc(sizeof(card));
    CardNode_Create(deck_head, -1, -1, NULL);
    lastObj = deck_head;

    //Generate deck of cards
    int num_cards = 0;
    int temp_face;
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
    
    char enter_menu; //comment this part out when game is finished.
    while (1)
    {
        printf("Enter game dev menu? (y/n)");
        scanf("%c", &enter_menu);

        if (enter_menu == 'n') {
            break;
        }
        else if (enter_menu == 'y') {
            testGame(deck_head, currObj, num_cards); //function to test functionality of program.
            break;
        }
        else {
            continue;
        }
    }

    //deal cards here



    free(deck_head);
    free(currObj);
    return 0;
}


void testGame(card* deck_head, card* currObj, int num_cards) {

    int user_inp;
    printf("\n----------------------------------------------------\n");
    printf("Development Menu\n");
    printf("1. Check shuffle functionality\n");
    printf("2, Check symbol print out\n");

    scanf("%d", &user_inp);
  
    if (user_inp == 1) {
        int num_shuffles;
        printf("How many times would you like to shuffle the deck: ");
        scanf("%d", &num_shuffles);

        printf("\nOriginal deck: \n");
        printDeck(deck_head, currObj); // check to see if deck formed correctly.

        printf("\nBeginning test\n");
        for (int i = 0; i < num_shuffles; i++) {
            shuffleCards(deck_head, currObj, num_cards);
            printf("\nShuffle #%d\n", i + 1);
            printDeck(deck_head, currObj);

        }
    }
    else if (user_inp == 2) {
        printf("\nPrinting symbols....\n");
        testUnicode(); //the output of these symbols work on windows and mac!
    }

}

void testUnicode() { //just a test for unicode characters. works on mac.

    printf(SPADE);
    printf(CLUB);
    printf(DIAMOND);
    printf(HEART);
    printf("\n");
}




