﻿// CMakeMain_Testing.c : Defines the entry point for the application.
//
//
// See final_project_notes.txt in the repo for the pseudocode.
//Test functions are below main(). Useful functions are above main().


#include "CMakeProject_Khalil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define HEART 'H'
#define DIAMOND 'D'
#define CLUB 'C'
#define SPADE 'S'


typedef struct card_s {			//can add or change to this but not delete any preexisting

    char suit; //s - spade, h - heart, d - diamond, c - club
    int face; //1 - ACE
    struct card_s* next; //card.next... this is a pointer to an address of type card.

} card;

typedef struct player_s {

    char name[100];
    struct card_s* hand;
    struct card_s* head;
    struct card_s* prev;

}player;

void compAskForCard(player* player_1, player* player_pc);
int askForCard(player* player_1, player* player_pc, int whos_turn);
void checkDeckForBooks(player* player_info, int* book_player, int* book_total, char player_books[]);
card* findCardFace(card* temp, int* face);
void deleteCard(card* temp, int face, char suit);
card* findCard(card* temp, int* face, char* suit);
void printDeck(card* deck_head, card* currObj);
void shuffleCards(card* deck_head, card* currObj, int num_cards);
void cardFoundOrNot(player* player_1, player* player_pc, int counter, card* deck_head);
void drawCard(card* player_info, card* deck_head); //WORKING ON IT

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

    char something = SPADE;

    if (thisCard->suit == 's') {
        printf("%d", thisCard->face);
        printf("%c", something);
        printf(" ");
    }
    else if (thisCard->suit == 'h') {
        printf("%d", thisCard->face);
        printf("%c", HEART);
        printf(" ");
    }
    else if (thisCard->suit == 'c') {
        printf("%d", thisCard->face);
        printf("%c", CLUB);
        printf(" ");
    }
    else if (thisCard->suit == 'd') {
        printf("%d", thisCard->face);
        printf("%c", DIAMOND);
        printf(" ");
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
    if (deck_head == NULL)
    {
        printf("FLAG: printDeck(), deck_head is null.\n");
    }
    else
    {
        currObj = deck_head->next;
        while (currObj != NULL) {
            CardNode_PrintNodeData(currObj);
            currObj = CardNode_GetNext(currObj);
        }
    }

}

card* findCard(card* temp, int* face, char* suit)
{
    card* curr = CardNode_GetNext(temp);
    while (curr != NULL)
    {
        if (curr->face == face && curr->suit == suit)
        {
            return curr;
        }
        curr = CardNode_GetNext(curr);
    }
    return NULL;

}

void deleteCard(card* temp, int face, char suit) {

    card* prev;
    card* target = findCard(temp, face, suit);

    if (target == NULL) {
        printf(""); //test, shouldn't need in final
    }
    else {
        card* prev = temp;
        if (prev->next == target) {
            temp->next = target->next;
        }
        else
        {
            while (prev->next != target) {
                prev = prev->next;
            }
            if (target->next == NULL) {
                prev->next = NULL;
            }
            else {
                prev->next = target->next;
            }
        }
        free(target);
    }
}

card* findCardFace(card* temp, int* face)
{
    card* curr = CardNode_GetNext(temp);
    while (curr != NULL)
    {
        if (curr->face == face)
        {
            return curr;
        }
        curr = CardNode_GetNext(curr);
    }
    return NULL;

}

void checkDeckForBooks(player* player_info, int* book_player, int* book_total, char player_books[]) //I think this is correct parameters to pass
{
    card* temp;

    for (int i = 1; i <= 9; ++i)
    {
        int count = 0;

        temp = player_info->head;

        for (int j = 0; j < 4; ++j)
        {
            temp = findCardFace(temp, i);

            if (temp != NULL)
            {
                ++count;
            }
            else if (temp == NULL)
            {
                break;
            }
            if (count == 4)     //if there's 4 face values found, delete them from hand and increment book
            {
                (*book_total)++;
                (*book_player)++;

                if (i == 1)
                {
                    player_books[i - 1] = 'A';
                }
                else
                {
                    player_books[i - 1] = (i + 48);
                }

                deleteCard(player_info->head, i, 'h');
                deleteCard(player_info->head, i, 'd');
                deleteCard(player_info->head, i, 's');
                deleteCard(player_info->head, i, 'c');
            }
        }
    }
}

void addCards(player* player_info, card** deck_head, int num_cards) //FIX ME
{
    //this function does indeed add cards to the player's deck

    //*deck_head = (*deck_head)->next;
    if ((*deck_head)->next == NULL || (*deck_head) == NULL)
    {
        printf("FLAG 1ST: Deck is empty.\n");
    }
    else
    {
        player_info->prev = player_info->head;
        for (int i = 0; i < num_cards; i++)
        {
            player_info->hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_info->hand, (*deck_head)->suit, (*deck_head)->face, NULL);
            CardNode_InsertAfter(player_info->prev, player_info->hand);
            player_info->prev = player_info->hand;
            deleteCard((*deck_head), (*deck_head)->face, (*deck_head)->suit);

            if ((*deck_head)->next == NULL) //if deck has no more cards (ex. 2 cards left in deck) then give 2 and exit function.
            {
                printf("\nDeck is empty");
                break;
            }

            *deck_head = (*deck_head)->next;
        }
    }


}

void drawCard(player* player_info, card* deck_head) //FIX ME
{
    //error at cardnode_create and cardnode_insertafter

    if (deck_head->next == NULL || deck_head == NULL)
    {
        printf("Deck is empty\n");
    }
    else
    {
        deck_head = deck_head->next;
        if (deck_head != NULL)
        {
            player_info->hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_info->hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(player_info->prev, player_info->hand);
            deleteCard(deck_head, deck_head->face, deck_head->suit);
            deck_head = deck_head->next;
        }
    }
}

int askForCard(player* player_1, player* player_pc, int* choice, int whos_turn) //organize function and split logic into diff functions for readability
{
    char choice_card;
    //int choice;
    int counter = 0;
    int choice_local;
    *choice = &choice_local;
    while (1)
    {
        if (whos_turn == 1) //player turn
        {
            printf("Your turn %s. Which card (A, 2-9) do you want to ask for? ", player_1->name);
            scanf(" %c", &choice_card);
            player_1->prev = player_1->head;
            if (choice_card == 'A') //iterate through the user's choice A, 2-9
            {
                choice_local = 1;
                for (int i = 0; i < 4; ++i) //if choice, ask for up to 4 cards (H,S,D,C) 
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)    //if face value found, copy to player deck and delete from comp deck
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '2')
            {
                choice_local = 2;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '3')
            {
                choice_local = 3;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '4')
            {
                choice_local = 4;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '5')
            {
                choice_local = 5;

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '6')
            {
                choice_local = 6;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '7')
            {
                choice_local = 7;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '8')
            {
                choice_local = 8;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_card == '9')
            {
                choice_local = 9;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice_local);
                    if (temp != NULL)
                    {
                        player_1->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_1->prev, player_1->hand);
                        deleteCard(player_pc->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else
            {
                printf("Enter only A, 2-9 for the card\n");
                continue; //print functions in next lines wont execute if 'continue' and reenter loop
            }
        }
        else //if whos_turn == 2, PC TURN
        {
            printf("PC's turn......\n");
            srand((int)time(0));
            choice_local = rand() % 9;

            if (choice_local == 1) //iterate through the user's choice A, 2-9
            {
                for (int i = 0; i < 4; ++i) //if choice, ask for up to 4 cards (H,S,D,C) 
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)    //if face value found, copy to player deck and delete from comp deck
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 2)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 3)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 4)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 5)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 6)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 7)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 8)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else if (choice_local == 9 || choice_local == 0)
            {
                if (choice_local == 0)
                {
                    choice_local = 9;
                }

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice_local);
                    if (temp != NULL)
                    {
                        player_pc->hand = (card*)malloc(sizeof(card));
                        CardNode_Create(player_pc->hand, temp->suit, temp->face, NULL);
                        CardNode_InsertAfter(player_pc->prev, player_pc->hand);
                        deleteCard(player_1->head, temp->face, temp->suit);
                        counter++;
                    }
                }
            }
            else //For debugging. Shouldnt ever reach condition in final game.
            {
                printf("Something went wrong....\n");
                printf("Choice: %d\n", *choice);
                exit(1);
            }

            char validate_input; //ask player for choice
            do
            {
                printf("Do you have card(s) with %d (y/n)?", choice_local);
                scanf(" %c", &validate_input);

            } while (validate_input != 'y' && validate_input != 'n');
        }
        return counter; //the player should be telling the truth. if not, it won't matter. 
    }
}

void deallocateMemory(card* head) //free allocated memory by passing in the heads of the lists
{
    card* curr = head;
    card* next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(void) {

    char player_name[100]; //may change later. names may not always be just 100 char long.
    player player_1; //also could change if we want extra credit. 
    player player_pc;
    int i;
    char player_books[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char comp_books[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

    printf("Enter your name: ");
    scanf("%s", player_1.name);
    printf("\n%s lets play go fish!\n", player_1.name);

    card* currObj = NULL;
    card* deck_head = NULL;
    card* deck_head_prev = NULL;
    card* lastObj = NULL;
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

    //printf("---------TESTING--------\n");
    printf("Original deck: \n"); //TESTING
    printDeck(deck_head, currObj);
    printf("\n");
    shuffleCards(deck_head, currObj, num_cards);
    printf("\nShuffled deck: \n");
    printDeck(deck_head, currObj);

    //deal cards here
    player_pc.hand = NULL; //make computer hand and linked list.
    player_pc.head = (card*)malloc(sizeof(card));
    player_pc.prev = NULL;
    CardNode_Create(player_pc.head, -1, -1, NULL);
    player_pc.prev = player_pc.head;

    player_1.hand = NULL; //make computer hand and linked list.
    player_1.head = (card*)malloc(sizeof(card));
    player_1.prev = NULL;
    CardNode_Create(player_1.head, -1, -1, NULL);
    player_1.prev = player_1.head;

    int toggle = 0; //manually toggle to hand card to each player 1 by 1.
    for (int i = 0; i < 6 * 2; i++)
    {
        if (toggle == 0) {
            player_pc.hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_pc.hand, deck_head->next->suit, deck_head->next->face, NULL);
            CardNode_InsertAfter(player_pc.head, player_pc.hand);
            player_pc.prev = player_pc.hand;
            toggle = 1;
        }
        else {
            player_1.hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_1.hand, deck_head->next->suit, deck_head->next->face, NULL);
            CardNode_InsertAfter(player_1.head, player_1.hand);
            player_1.prev = player_1.hand;
            toggle = 0;
        }
        deck_head_prev = deck_head;
        deck_head = deck_head->next;
        deleteCard(deck_head, deck_head->face, deck_head->suit);
    }

    printf("\nDeck after dealing cards: \n");
    printDeck(deck_head, currObj);
    printf("\n");
    printf("\nComputer hand:\n");      //TESTING
    printDeck(player_pc.head, player_pc.hand);
    printf("\nPlayer hand:\n");
    printDeck(player_1.head, player_1.hand);
    printf("\n----------------------\n");

    printf("Cards are distributed!\n");
    printf("This is your hand: ");
    printDeck(player_1.head, player_1.hand);
    printf("\n");

    char validate_continue;
    do {
        printf("Continue? (y/n)\nYou will start the game if you press 'y': ");
        scanf(" %c", &validate_continue);

        if (validate_continue != 'y') {
            printf("\n~~~~~~~~~~~~~~~~Cry more.~~~~~~~~~~~~~~~~~\n");
        }

    } while (validate_continue != 'y');

    int book_total = 0; //initially 0 total points and 0 per player
    int book_player = 0;
    int book_computer = 0;
    int whos_turn = 1; // 1 = player_1 turn... 2 = player_pc turn
    //ask for card here. game 'begins'
    while (book_total != 9) //game stops when player has 9 books (sets).
    {


        checkDeckForBooks(&player_1, &book_player, &book_total, player_books);
        checkDeckForBooks(&player_pc, &book_computer, &book_total, comp_books);

        if (deck_head == NULL)
        {   
            printf("\n-----Deck is empty!------\n\n");
            //return 0;
        }
        int choice; //pass choice as pointer to return both counter and choice.
        int counter;
        counter = askForCard(&player_1, &player_pc, &choice, whos_turn); //game starts with player asking pc 

        if (counter == 0) //go fish 
        {
            printf("Go Fish!\n");
            if (whos_turn == 1) //for player_1
            {
                drawCard(&player_1, deck_head, whos_turn); //works when you pass in player_1 and not its address.... why?
                deleteCard(deck_head, deck_head->face, deck_head->suit); //commented out and all 9 books show but something wierd happens....
                if (choice == player_1.hand->face) {
                    //if drawCard has the suit that player asked, then its the player's turn again
                    printf("The card drawn is the same as what was asked! Go again.\n");
                }
                else {
                    whos_turn = 2;
                }
            }
            else
            {
                printf("PC didnt find a card....\n");
                drawCard(&player_pc, deck_head, whos_turn);
                deleteCard(deck_head, deck_head->face, deck_head->suit);
                if (choice == player_pc.hand->face) {
                    //if drawCard has the suit that player asked, then its the player's turn again
                    printf("The card drawn is the same as what was asked! PC is going again.\n");
                }
                else {
                    whos_turn = 1;
                }
            }
            deck_head = deck_head->next; //move deck head to avoid duplicates      
        }
        else //card was found
        {
            switch (whos_turn)
            {
            case 1:
                printf("You found a card! Go again!\n");
                break;
            case 2:
                printf("PC found a card! Going again.\n");
                break;
            default:
                printf("Something went wrong...\n");
                exit(1);
            }
        }

        printf("\nYour hand: ");
        printDeck(player_1.head, player_1.hand);
        printf("\n\n");

        if (player_1.head->next == NULL || player_pc.head->next == NULL)
        {
            //if player's hand is empty, add cards from the deck.
            if (player_1.head->next == NULL) {
                printf("Adding cards to your deck.....\n");

                if (deck_head->next == NULL || deck_head == NULL)
                {
                    printf("No more cards left in deck!\n");
                    break; //break because if no cards in deck and player deck is empty then the game ends.
                    //break;
                }
                else
                {
                    addCards(&player_1, &deck_head, 6);
                }
            }
            else {
                printf("Adding cards to PC's deck.....\n");

                if (deck_head->next == NULL || deck_head == NULL)
                {
                    printf("No more cards left in deck!\n");
                    break;
                }
                else
                {
                    addCards(&player_pc, &deck_head, 6);
                }
            }
            //deck_head = deck_head->next; //testing to see if error is here....
        }


        printf("\nTotal books: %d\n", book_total);
        printf("\nPlayer books: %d", book_player);

        printf("\nYour current books: [");
        for (i = 0; i < 9; ++i)
        {
            printf("%c ", player_books[i]);
        }
        printf("]\n");

        printf("Comp books: %d\n", book_computer);
        printf("Comp current books: [");
        for (i = 0; i < 9; ++i)
        {
            printf("%c ", comp_books[i]);
        }
        printf("]\n");


        printf("\n---------------------------------------\n");
        printf("\nDeck: ");
        printDeck(deck_head, currObj);
        printf("\nPC hand: ");
        printDeck(player_pc.head, player_pc.hand);
        printf("\nPlayer hand: ");
        printDeck(player_1.head, player_1.hand);
        printf("\n---------------------------------------\n");
        printf("\n---------------------------------------\n");
    }


    checkDeckForBooks(&player_1, &book_player, &book_total, player_books);
    checkDeckForBooks(&player_pc, &book_computer, &book_total, comp_books);

    printf("\nTotal books: %d\n", book_total);
    printf("\nPlayer books: %d", book_player);

    printf("\nYour current books: [");
    for (i = 0; i < 9; ++i)
    {
        printf("%c ", player_books[i]);
    }
    printf("]\n");

    printf("Comp books: %d\n", book_computer);
    printf("Comp current books: [");
    for (i = 0; i < 9; ++i)
    {
        printf("%c ", comp_books[i]);
    }
    printf("]\n");


    printf("\n---------------------------------------\n");
    printf("\nTotal Books = %d\n", book_total);

    if (book_player > book_computer)
    {
        printf("The winner is %s with %d books!!!\n\n", player_1.name, book_player);
    }
    else
    {
        printf("PC is the winner with %d books!!!\n\n", book_computer);
    }

    deallocateMemory(deck_head);
    deallocateMemory(player_1.head);
    deallocateMemory(player_pc.head);
    //free(player_1.hand);
    //free(player_pc.hand);
    //free(currObj);

    return 0;
}