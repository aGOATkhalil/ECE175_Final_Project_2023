#include "CMakeProject1.h"

    //Rayce Bacchus & Khalil Gatto
    //11-4-2023

    /*
    ************************************************************************************************
                        USE LINKED LISTS OR ELSE GET 0
    ************************************************************************************************
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

void Node_Create(card* thisNode, char name_init[], int age_init, card* nextLoc)
{
    thisNode->age = age_init;
    strcpy(thisNode->name, name_init);
    thisNode->next = nextLoc;
}

void Node_InsertAfter(card* thisNode, card* newNode)
{
    card* tmpNext = NULL;

    tmpNext = thisNode->next; // Remember next
    thisNode->next = newNode; // this -- new -- ?
    newNode->next = tmpNext;  // this -- new -- next
}

void Node_PrintNodeData(card* thisNode)
{
    printf("%s %d\n", thisNode->suit, thisNode->face);
}

Node_GetNext(card* thisNode)
{
    return thisNode->next;
}

void print_list(card* pt)
{
    card* currObj = Node_GetNext(pt); //skip dummy head node
    while (currObj != NULL) {
        Node_PrintNodeData(currObj);
        currObj = Node_GetNext(currObj);
    }
}

void find_age(card* pt, int min, int max)
{
    card* curr = Node_GetNext(pt);

    while (curr != NULL)
    {
        if (curr->age <= max && curr->age >= min)
        {
            Node_PrintNodeData(curr);
        }
        curr = Node_GetNext(curr);
    }
}

void delete_node(card* pt, char delname[]) {

    card* prev;
    card* target = find_name(pt, delname);
    card* currnode;
    if (target == NULL) {
        printf("no node with name %s\n", delname);
    }
    else
    {
        if (prev->next == target)
        {
            prev->next = target->next;
        }
        else
        {
            while (prev->next != target)
            {
                prev = prev->next;
            }
            if (target->next == NULL) //last node
            {
                prev->next = NULL;
            }
            else
            {
                prev->next = target->next;
            }
        }
        free(target);
    }
}

int main(void) 
{
    //blah blah stuff blah blah
    //balls

    char player_name[100]; //may change later. names may not always be just 100 char long.
    printf("Enter your name: ");
    scanf("%s", player_name);
    printf("\n%s lets play go fish!\n", player_name);

    //Playerhead//dummy->node1->node2->node3->node4->node5->node6->NULL
    //Computerhead//dummy->node1->node2->node3->node4->node5->node6->NULL
    //Delete 12 from Deck linked list

    array = (card*)malloc(37 * sizeof(card));

    return 0;
}