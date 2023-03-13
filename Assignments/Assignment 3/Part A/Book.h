
// Part A Assignment 3
// Create By MHD Rida Tarabishi
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"



struct Book
{
    long bookId;
    int bookPublished;
    char bookAuthor[100];
    char bookTitle[100];
    char bookRating;
    struct Book *nextPtr;
};

typedef struct Book book;
typedef struct Book *ItemPtr;




ItemPtr push(ItemPtr topPtr, long id, int published, char author[100], char title[100],char rating);
ItemPtr pop(ItemPtr topPtr);
int isEmpty(ItemPtr topPtr);
void topOfStack(ItemPtr topPtr);
void bottomOfStack(ItemPtr topPtr);
void printStack(ItemPtr topPtr);
void instructions(void);

// Extra Methods

// responsible for printing a single node, given a ptr to it
// to avoid many print statments every time a node needs to be printed
void printNode(ItemPtr node);

//checks for duplicate book id
bool bookExists(ItemPtr sPtr, long id);



// Push Method
ItemPtr push(ItemPtr topPtr, long id, int published, char author[100], char title[100],char rating)
{
    // Initialise pointer for new StackNode
    ItemPtr newPtr;

    // Create memory for new StackNode
    newPtr = malloc(sizeof(ItemPtr));

    // Push new StackNode onto top-of-stack
    if(newPtr != NULL)
    {
        newPtr->bookId = id;
        newPtr->bookPublished=published;

        strcpy(newPtr->bookAuthor,author);
        strcpy(newPtr->bookTitle,title);

        newPtr->bookRating=rating;

        newPtr->nextPtr = topPtr;
        topPtr = newPtr;
    }
    else
    {
        printf("Book not inserted. No memory available.\n");
    }
    return topPtr;
}


//Pop Method, remove from topPtr
ItemPtr pop(ItemPtr topPtr)
{
    // Initialise temporary pointer to hold address of StackNode to pop
    ItemPtr tempPtr;
    int popValue = 0;
    // isolate StackNode to be deleted
    tempPtr = topPtr;
    // inform user of Node to be popped
    popValue = topPtr->bookId;
    printf("Book with id: %d is being removed...\n", popValue);

    // update topPtr
    topPtr = topPtr->nextPtr;
    // deallocate memory
    free(tempPtr);
    return topPtr;
}

//Print Stack
void printStack(ItemPtr topPtr)
{
    ItemPtr currentPtr = topPtr;
    if(isEmpty(topPtr))
    {
        puts("Book Library is Empty \n");
    }
    else
    {
        printf("List of Books: \n");
        while(currentPtr != NULL)
        {
            // print current node information
            printNode(currentPtr);
            // move onto the next node
            currentPtr = currentPtr->nextPtr;
        }
        printf("End of Books Library\n");
    }
}

int isEmpty(ItemPtr topPtr)
{
    // return true if topPtr is NULL of False otherwise;
    return topPtr == NULL;
}

void topOfStack(ItemPtr topPtr)
{
    // display value at the top-of-stack
    puts("Book at the top is: \n");
    printNode(topPtr);
}

void bottomOfStack(ItemPtr topPtr)
{
    ItemPtr previousPtr = NULL, currentPtr = topPtr;
    // display value at the bottom-of-stack
    while(currentPtr != NULL)
    {
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;

    }
    printNode(previousPtr);
}


//book with id exists
bool bookExists(ItemPtr sPtr, long id)
{
    ItemPtr previousPtr = NULL, currentPtr = sPtr;
    while(currentPtr != NULL)
    {
        if(currentPtr->bookId!=id)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
        else
        {
            printf("Book with ID %ld Already Exists", id);
            return true;
        }
    }
    return false;
}




void printNode(ItemPtr node)
{
    printf("ID: %ld \n",node->bookId);
    printf("Published: %d \n",node->bookPublished);
    printf("Auhtor: %s \n", node->bookAuthor);
    printf("Title : %s \n", node->bookTitle);
    printf("Rating : %c \n",node->bookRating);
    printf("----------------------------------------------- \n");
}

void instructions(void)
{
    printf("Enter choice:\n"
           "1 Push a value on the stack\n"
           "2 Pop a value off the stack\n"
           "3 Top of the stack \n"
           "4 Bottom of the stack\n"
           "5 Print the stack\n"
           "6 to end the program\n");
}