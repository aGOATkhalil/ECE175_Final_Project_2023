// CMakeMain_Testing.c : Defines the entry point for the application.
//

// CMakeProject_Testing.c : Defines the entry point for the application.
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
    int face; //1 = ACE, 2-9
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

    char something = SPADE;

    if (thisCard->suit == 's') {
        printf("%d", thisCard->face);
        printf("%c", something);
        printf("\n");
    }
    else if (thisCard->suit == 'h') {
        printf("%d", thisCard->face);
        printf("%c", HEART);
        printf("\n");
    }
    else if (thisCard->suit == 'c') {
        printf("%d", thisCard->face);
        printf("%c", CLUB);
        printf("\n");
    }
    else if (thisCard->suit == 'd') {
        printf("%d", thisCard->face);
        printf("%c", DIAMOND);
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

int numCardsInDeck(card* currObj, card* deck_head)
{
    int num_cards = 0;
    currObj = deck_head->next;

    while (currObj != NULL)
    {
        ++num_cards;
    }
    return num_cards;
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

    card* prev = temp;
    card* target = findCard(temp, face, suit);

    if (target == NULL) {
        printf(""); //test, shouldn't need in final
    }
    else {
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

void checkDeckForBooks(card* deck_head, card* player_hand, card* prev_player_card, int* book_player, int* book_total, char player_books[])
{
    for (int i = 1; i <= 9; ++i)
    {
        int count = 0;
        card* temp = findCardFace(deck_head, i);

        if (temp != NULL)
        {
            ++count;
        }
        if (count == 4)
        {
            //syntax?
            ++*book_total;
            ++*book_player;

            if (i == 1)
            {
                player_books[i - 1] = 'A';
            }
            else
            {
                player_books[i - 1] = i;
            }

            //Delete each card of the face value from the deck
            //DOES NOT WORK YET 
            //FIX ME
            deleteCard(player_hand, temp->face, 'H');
            deleteCard(player_hand, temp->face, 'D');
            deleteCard(player_hand, temp->face, 'S');
            deleteCard(player_hand, temp->face, 'C');
        }
    }
}

void playerAskForCard(card* comp_deck_head, card* comp_hand, card* prev_player_card, card* player_hand, card* player_deck_head)
{
    char choice_card;
    int choice;
    while (1)
    {
        printf("Which card (A, 2-9) do you want to ask for? ");
        scanf(" %c", &choice_card);

        if (choice_card == 'A') //iterate through the user's choice A, 2-9
        {
            choice = 1;
            for (int i = 0; i < 4; ++i) //if choice, ask for up to 4 cards (H,S,D,C) 
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)    //if face value found, copy to player deck and delete from comp deck
                {
                    //can possibly make this a function later
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '2')
        {
            choice = 2;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '3')
        {
            choice = 3;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '4')
        {
            choice = 4;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '5')
        {
            choice = 5;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '6')
        {
            choice = 6;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '7')
        {
            choice = 7;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '8')
        {
            choice = 8;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else if (choice_card == '9')
        {
            choice = 9;

            for (int i = 0; i < 4; ++i)
            {
                card* temp = findCardFace(comp_deck_head, choice);
                if (temp != NULL)
                {
                    player_hand = (card*)malloc(sizeof(card));
                    CardNode_Create(player_hand, temp->suit, temp->face, NULL);
                    CardNode_InsertAfter(prev_player_card, player_hand);
                    deleteCard(comp_deck_head, temp->face, temp->suit);
                }
            }
        }
        else
        {
            printf("Enter only A, 2-9 for the card\n");
            continue; //print functions in next lines wont execute if 'continue' and reenter loop
        }

        printDeck(comp_deck_head, comp_hand);
        printf("\n");
        printDeck(player_deck_head, player_hand);
        printf("\n");
    }
}

void compAskForCard()
{

}

void testUnicode(); //just a test for unicode characters. works on mac
void testGame(card* deck_head, card* currObj, int num_cards); //dev menu. number of tests in this function.
card* copyDeck(card* list);

int main(void) {

    char player_name[100]; //may change later. names may not always be just 100 char long.
    player player_1; //also could change if we want extra credit. 
    player player_2;
    int i;
    int j;
    char player_books[10];
    char comp_books[10];

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
    for (i = 1; i < 10; i++) //number of faces... 1 = ACE
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

    card* original_deck_head = NULL;
    original_deck_head = (card*)malloc(sizeof(card));
    original_deck_head = copyDeck(deck_head); //IGNORE FOR NOW

    printf("Original deck: \n"); //TESTING PURPOSES
    printDeck(deck_head, currObj);
    printf("\n");
    //shuffleCards(deck_head, currObj, num_cards);
    printf("\nShuffled deck: \n");
    printDeck(deck_head, currObj);
    printf("\n");

    //deal cards here
    card* comp_hand = NULL; //make computer hand and linked list
    card* comp_deck_head = (card*)malloc(sizeof(card));
    card* prev_comp_card = NULL;
    CardNode_Create(comp_deck_head, -1, -1, NULL);
    prev_comp_card = comp_deck_head;

    card* player_hand = NULL; //make player hand and linked list
    card* player_deck_head = (card*)malloc(sizeof(card)); //make player hand and linked list
    card* prev_player_card = NULL;
    CardNode_Create(player_deck_head, -1, -1, NULL);
    prev_player_card = player_deck_head;

    deck_head = deck_head->next;
    int toggle = 0; //manually toggle to hand card to each player 1 by 1 //// likely modify later
    for (i = 0; i < 6 * 2; i++)
    {
        if (toggle == 0) { //deal to computer
            comp_hand = (card*)malloc(sizeof(card));
            CardNode_Create(comp_hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(prev_comp_card, comp_hand);
            toggle = 1;
        }
        else { //deal to player
            player_hand = (card*)malloc(sizeof(card));
            CardNode_Create(player_hand, deck_head->suit, deck_head->face, NULL);
            CardNode_InsertAfter(prev_player_card, player_hand);
            toggle = 0;
        }
        deleteCard(deck_head, deck_head->face, deck_head->suit); //delete dealed card from main deck
        deck_head = deck_head->next;
    }

    printf("\nComputer hand:\n");           //remove for final game, debugging purposes
    printDeck(comp_deck_head, comp_hand);
    printf("\nPlayer hand:\n");
    printDeck(player_deck_head, player_hand);

    int book_total = 0; //initially 0 total points and 0 per player/comp
    int book_player = 0;
    int book_computer = 0;

    while (book_total != 9) //Game 'begins'
    {
        checkDeckForBooks(player_deck_head, player_hand, prev_player_card, &book_player, &book_total, player_books);
        checkDeckForBooks(comp_deck_head, comp_hand, prev_comp_card, &book_computer, &book_total, comp_books);

        playerAskForCard(comp_deck_head, comp_hand, prev_player_card, player_hand, player_deck_head);

        //compAskForCard implement to a function after, basically same as player
        //probably better to make general function and pass parameters for it for each player
        //will fix/implement later
        
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
            testGame(deck_head, currObj, comp_deck_head, comp_hand, original_deck_head, num_cards); //function to test functionality of program.
            break;
        }
        else {
            continue;
        }
    }

    free(deck_head);
    free(currObj);
    free(comp_hand);
    free(comp_deck_head);
    free(original_deck_head);
    free(player_deck_head);
    free(player_hand);

    return 0;
}


void testGame(card* deck_head, card* currObj, card* comp_deck_head, card* comp_hand, card* original_deck_head, int num_cards) {

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
        else if (user_shuffle_inp == 2) {
            printf("\n");
            printDeck(deck_head, currObj);
            printf("\n");
            printDeck(original_deck_head, currObj);
            printf("Not available. Still building\n");

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
        printDeck(comp_deck_head, comp_hand); //the deck is seperate from a player's hand.
    }
    else if (user_inp == 4) {
        printf("\nDeck:\n");
        printDeck(deck_head, currObj);

    }

}

card* copyDeck(card* list) { //FIX ME! NOT WORKING YET. Not totally needed.

    // Part 1 - the null list
    if (list == NULL) return NULL;

    // Part 2 - the head element
    card* newHead = (card*)malloc(sizeof(card));

    // Part 3 - the rest of the list
    card* p = newHead;
    list = list->next;
    while (list != NULL) {
        p->next = (card*)malloc(sizeof(card));
        p = p->next;
        list = list->next;
    }
    p->next = NULL;  // terminate last element.
}

void testUnicode() { //just a test for unicode characters. works on mac.

    printf("%c", SPADE);
    printf("%c", CLUB);
    printf("%c", DIAMOND);
    printf("%c", HEART);
    printf("\n");
}