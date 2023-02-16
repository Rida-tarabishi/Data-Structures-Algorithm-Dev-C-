//
// Created by Rida Tarabishi on 2023-02-15.
//

// Codes wriiten on white-board in class

#include <stdlib.h>
#include <stdio.h>

struct Book {
    char id[10];
    int published;
    char author[50];
    char title[100];
    struct Book *next;
};

typedef struct book Book;
typedef struct book *ItemPtr;


ItemPtr makeItem (int value)
{
    ItemPtr np = (ItemPtr) malloc (sizeof (Book));
    np->name = value;
    np->next = NULL;
    return np;
}

ItemPtr addItem (ItemPtr sPtr, int value)
{
    ItemPtr newPtr, currPtr, prevPtr;
    newPtr = makeItem (value);
    prevPtr = NULL;
    currPtr = sPtr;
    while (currPtr != NULL && value > currPtr->name)
    {
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }

    if (prevPtr == NULL)
    {				// inserting at the start of the list
        newPtr->next = sPtr;
        sPtr = newPtr;		// start of list has now changed
    }
    else
    {
        newPtr->next = currPtr;
        prevPtr->next = newPtr;
    }

    return sPtr;
}

void printList (ItemPtr sPtr)
{
    if (sPtr == NULL)
    {
        printf ("\nThere are no Items to be Printed\n");
    }
    else
    {
        printf ("The Items in the List Are As Follows: \n");
        while (sPtr != NULL)
        {
            printf ("%d  ", sPtr->name);
            sPtr = sPtr->next;
        }
    }
}



