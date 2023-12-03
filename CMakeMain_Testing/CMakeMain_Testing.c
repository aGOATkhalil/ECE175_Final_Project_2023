// CMakeMain_Testing.c : Defines the entry point for the application.
//
//
// See final_project_notes.txt in the repo for the pseudocode.
//Test functions are below main(). Useful functions are above main().


#include "CMakeMain_Testing.h"
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
    //struct card_s* next;

}player;

void compAskForCard(player* player_1, player* player_pc);
int askForCard(player* player_1, player* player_pc,int whos_turn);
void checkDeckForBooks();
card* findCardFace(card* temp, int* face);
void deleteCard(card* temp, int face, char suit);
card* findCard(card* temp, int* face, char* suit);
void printDeck(card* deck_head, card* currObj);
void shuffleCards(card* deck_head, card* currObj, int num_cards);
void testUnicode(); //just a test for unicode characters.
void testGame(card* deck_head, card* currObj, int num_cards); //dev menu. number of tests in this function.
void validateCardChoice(player* player_1, player* player_pc, int choice); //WORKING ON IT
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

void dealCards(card* deck_head, player* player_1, player* player_pc) { //cards are not being deleted from the deck as we draw them...


    //deal cards here
    player_pc->hand = NULL; //make computer hand and linked list.
    player_pc->head = (card*)malloc(sizeof(card));
    player_pc->prev = NULL;
    CardNode_Create(player_pc->head, -1, -1, NULL);
    player_pc->prev = player_pc->head;

    player_1->hand = NULL; //make computer hand and linked list.
    player_1->head = (card*)malloc(sizeof(card));
    player_1->prev = NULL;
    CardNode_Create(player_1->head, -1, -1, NULL);
    player_1->prev = player_1->head;

  
    deck_head = deck_head->next;
    int toggle = 0; //manually toggle to hand card to each player 1 by 1.
    for (int i = 0; i < 6 * 2; i++)
    {
        if (toggle == 0) {
            player_pc->hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_pc->hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(player_pc->prev, player_pc->hand);
            player_pc->prev = player_pc->hand;
            toggle = 1;
        }
        else {
            player_1->hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_1->hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(player_1->prev, player_1->hand);
            player_1->prev = player_1->hand;
            toggle = 0;
        }
        deleteCard(deck_head, deck_head->face, deck_head->suit);
        deck_head = deck_head->next;
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

void checkDeckForBooks() //huh?
{



}

void validateCardChoice(player* player_1, player* player_pc, int choice) //FIX ME! Function doesnt work strangely.
{
    card* temp = findCardFace(player_pc->head, choice);
    if (temp != NULL)    //if face value found, copy to player deck and delete from comp deck
    {
        player_1->hand = (card*)malloc(sizeof(card));
        CardNode_Create(player_1->hand, temp->suit, temp->face, NULL);
        CardNode_InsertAfter(player_1->prev, player_1->hand);
        deleteCard(player_pc->head, temp->face, temp->suit);
    }
}

void drawCard(player* player_info, card* deck_head)
{
    //error at cardnode_create and cardnode_insertafter
    deck_head = deck_head->next;
    if (deck_head != NULL)
    {
        player_info->hand = (card*)malloc(sizeof(card));
        CardNode_Create(player_info->hand, deck_head->suit, deck_head->face, NULL);
        CardNode_InsertAfter(player_info->prev, player_info->hand);
        deleteCard(deck_head, deck_head->face, deck_head->suit);
        deck_head = deck_head->next;
    }
    else
    {
        printf("Deck is empty");
    }
}

int askForCard(player* player_1, player* player_pc, int whos_turn) //organize function and split logic into diff functions for readability
{
    char choice_card;
    int choice;
    
    while (1)
    {
        int counter = 0;
        if (whos_turn == 1) //player turn
        {
            printf("Your turn %s. Which card (A, 2-9) do you want to ask for? ", player_1->name);
            scanf(" %c", &choice_card);

            if (choice_card == 'A') //iterate through the user's choice A, 2-9
            {
                choice = 1;
                for (int i = 0; i < 4; ++i) //if choice, ask for up to 4 cards (H,S,D,C) 
                {
                    //validateCardChoice(&player_1, &player_pc, &choice)
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 2;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 3;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 4;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 5;

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 6;

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 7;

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 8;

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
                choice = 9;
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_pc->head, choice);
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
            choice = rand() % 9;

            if (choice == 1) //iterate through the user's choice A, 2-9
            {
                for (int i = 0; i < 4; ++i) //if choice, ask for up to 4 cards (H,S,D,C) 
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 2)
            {   
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 3)
            {             
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 4)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 5)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 6)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 7)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 8)
            {
                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
            else if (choice == 9 || choice == 0)
            {
                if (choice == 0)
                {
                    choice = 9;
                }

                for (int i = 0; i < 4; ++i)
                {
                    card* temp = findCardFace(player_1->head, choice);
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
                printf("Choice: %d\n", choice);
                exit(1);
            }
        }

        return counter;
    }
}

int main(void) {

    char player_name[100]; //may change later. names may not always be just 100 char long.
    player player_1; //also could change if we want extra credit. 
    player player_pc;

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
    //printf("Original deck: \n"); //TESTING
    //printDeck(deck_head, currObj);
    //printf("\n");
    //shuffleCards(deck_head, currObj, num_cards);
    //printf("\nShuffled deck: \n");
    //printDeck(deck_head, currObj);

    //deal cards here
    //NOTE. THIS WORKS IN MAIN BUT NOT IN A FUNCTION. POINTER ERRORS AND WHAT NOT
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

    deck_head = deck_head->next;
    int toggle = 0; //manually toggle to hand card to each player 1 by 1.
    for (int i = 0; i < 6 * 2; i++)
    {
        if (toggle == 0) {
            player_pc.hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_pc.hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(player_pc.prev, player_pc.hand);
            player_pc.prev = player_pc.hand;
            toggle = 1;
        }
        else {
            player_1.hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_1.hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(player_1.prev, player_1.hand);
            player_1.prev = player_1.hand;
            toggle = 0;
        }
        deleteCard(deck_head, deck_head->face, deck_head->suit);
        deck_head = deck_head->next;
    }
   
    //printf("Deck after dealing cards: \n"); 
    //printDeck(deck_head, currObj);
    //printf("\n");
    //printf("\nComputer hand:\n");      //TESTING
    //printDeck(player_pc.head, player_pc.hand);
    //printf("\nPlayer hand:\n");
    //printDeck(player_1.head, player_1.hand);
    //printf("\n----------------------\n");


    printf("Cards are distributed!\n");
    printf("This is your hand: \n");
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
    int counter = 1;

    //ask for card here. game 'begins'
    while (book_total != 9) //game stops when player has 9 books (sets).
    {  
        if (deck_head == NULL)
        {
            printf("\n-----Deck is empty!------\n\n");
            return 0;
        }

        counter = askForCard(&player_1, &player_pc, whos_turn); //game starts with player asking pc 

        //if (whos_turn == 1) {
        //    //system("cls");
        //    printf("Your hand: ");
        //    printDeck(player_1.head, player_1.hand);
        //    printf("\n\n");
        //}

        if (counter == 0) //go fish 
        {
            if (whos_turn == 1) //for player_1
            {
                drawCard(&player_1, deck_head, whos_turn); //works when you pass in player_1 and not its address.... why?
                printf("\nYour hand: ");
                printDeck(player_1.head, player_1.hand);
                printf("\n\n");
                whos_turn = 2;
            }
            else
            {
                printf("PC didnt find a card....\n");
                drawCard(&player_pc, deck_head, whos_turn);
                whos_turn = 1;
            }
            deck_head = deck_head->next; //move deck head to avoid duplicates
            printf("Go Fish!\n\n");

        }
        else //card was found
        {
            switch (whos_turn)
            {
                case 1:
                    printf("You found a card! Go again!\n");
                    printf("\nYour hand: ");
                    printDeck(player_1.head, player_1.hand);
                    printf("\n\n");
                    break;
                case 2:
                    printf("PC found a card! Going again.\n");
                    break;
                default:
                    printf("Something went wrong...\n");
                    exit(1);
            }

        }

        //printf("Deck:\n");
        //printDeck(deck_head, currObj);
        //printf("\nPC hand:\n");
        //printDeck(player_pc.head, player_pc.hand);
        //printf("\nPlayer hand:\n");
        //printDeck(player_1.head, player_1.hand);
        //printf("\n");

    }


    char enter_menu; //comment this part out when game is finished. always put at bottom.
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

    free(deck_head);
    free(currObj);
    free(player_pc.hand);
    free(player_pc.head);
    free(player_1.head);
    free(player_1.hand);

    return 0;
}



void testGame(card* deck_head, card* currObj, int num_cards) {

    int user_inp;
    printf("\n----------------------------------------------------\n");
    printf("Development Menu\n");
    printf("1. Check shuffle functionality\n");
    printf("2, Check symbol print out\n");
    printf("3. Check handing cards functinoality\n");
    printf("4. Show deck\n");
    printf("\n----------------------------------------------------\n");
    scanf("%d", &user_inp);

    if (user_inp == 1) {
        int num_shuffles;
        int user_shuffle_inp;
        printf("Choose one.\n");
        printf("1. Shuffle deck n times\n");
        printf("2. Check to see if all cards are in deck\n");
        scanf("%d", &user_shuffle_inp);

        if (user_shuffle_inp == 1) {

            printf("1. How many times would you like to shuffle the deck: ");
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

    }
    else if (user_inp == 2) {
        printf("\nPrinting symbols....\n");
        testUnicode(); //the output of these symbols work on windows and mac!
    }
    else if (user_inp == 3) {
        printf("Shuffled deck\n");
        printDeck(deck_head, currObj);
        printf("\nComputer deck: \n");
        //printDeck(comp_deck_head, comp_hand); //FIX ME
    }
    else if (user_inp == 4) {
        printf("\nDeck:\n");
        printDeck(deck_head, currObj);

    }

}

void testUnicode() { //just a test for unicode characters. works on mac.

    printf("%c", SPADE);
    printf("%c", CLUB);
    printf("%c", DIAMOND);
    printf("%c", HEART);
    printf("\n");
}