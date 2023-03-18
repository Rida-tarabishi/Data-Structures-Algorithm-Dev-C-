
// Part B Assignment 3
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
typedef struct Book *BookQueuePtr;



// functions
void enqueue(BookQueuePtr *headPtr, BookQueuePtr *tailPtr, long id, int published, char author[100], char title[100],char rating );
void dequeue(BookQueuePtr *headPtr, BookQueuePtr *tailPtr, BookQueuePtr head);
bool isEmpty(BookQueuePtr headPtr );
void printQueue( BookQueuePtr headPtr );
void front(BookQueuePtr headPtr );
void tail(BookQueuePtr tailPtr );
void instructions( void );

// responsible for printing a single node
// to avoid many print statments every time a book info needs to be printed
void printNode(BookQueuePtr bookPtr);



// insert a book at Queue Tail
void enqueue(BookQueuePtr *headPtr, BookQueuePtr *tailPtr, long id, int published, char author[100], char title[100],char rating )
{
    // ptr to store the address of the new book
    BookQueuePtr newPtr;

    // create memory for the new book
    newPtr = malloc(sizeof(book));

    if (newPtr != NULL)
    {
        newPtr->bookId = id;
        newPtr->bookPublished = published;
        strcpy(newPtr->bookAuthor,author);
        strcpy(newPtr->bookTitle,title);
        newPtr->bookRating =rating;
        newPtr->nextPtr = NULL;

        if (*headPtr == NULL)
        {
            *headPtr = newPtr;
        }
        else
        {
            (*tailPtr)->nextPtr = newPtr;
        }
        *tailPtr = newPtr;
    }
    else{
        puts("\n Memory Error \n");
    }

}

// check if Queue is Empty
bool isEmpty(BookQueuePtr headPtr )
{
    return headPtr == NULL;
}

// remove book from Queue Head
void dequeue(BookQueuePtr *headPtr, BookQueuePtr *tailPtr, BookQueuePtr head )
{
    if(isEmpty(head))
    {
        puts("Nothing to De-Queue");
    }
    else
    {
        //isolate book to be deleted
        BookQueuePtr tempPtr;
        tempPtr = *headPtr;

        //print book to be deleted
        printf("The following book is being deleted: \n");
        printNode(tempPtr);

        // update headPtr
        *headPtr = (*headPtr)->nextPtr;
        // if queue is empty, update tailPtr
        if (*headPtr == NULL)
        {
            *tailPtr = NULL;
        }
        // free memory of tempPtr
        free(tempPtr);
    }
}



//Check if book with same id exists in Queue
bool bookExists(BookQueuePtr headPtr, long id)
{
    BookQueuePtr previousPtr = NULL, currentPtr = headPtr;
    while(currentPtr != NULL)
    {
        if(currentPtr->bookId!=id)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
        else
        {
            printf("\n Book with ID %ld Already Exists \n", id);
            return true;
        }
    }
    return false;
}


// Print Methods:

//prints item in the front
void front(BookQueuePtr headPtr)
{
    if(isEmpty(headPtr))
    {
        puts(" \n No Books in Queue \n");
    }
    else
    {
        printf("Front of Queue is: \n");
        printNode(headPtr);
    }

}

//prints item in the back
void tail(BookQueuePtr tailPtr )
{
    if(isEmpty(tailPtr))
    {
        puts("\n No Books in Queue \n");
    }
    else
    {
        printf("Back of Queue is: \n");
        printNode(tailPtr);
    }

}


//Print specific book
void printNode(BookQueuePtr bookPtr)
{
    printf("----------------------------------------------- \n");
    printf("ID: %ld \n",bookPtr->bookId);
    printf("Published: %d \n",bookPtr->bookPublished);
    printf("Auhtor: %s \n", bookPtr->bookAuthor);
    printf("Title : %s \n", bookPtr->bookTitle);
    printf("Rating : %c \n",bookPtr->bookRating);
    printf("----------------------------------------------- \n");
}

// print entire Queue
void printQueue(BookQueuePtr headPtr )
{
    // set currentPtr at head
    BookQueuePtr currentPtr = headPtr;

    // if queue is empty
    if (isEmpty(headPtr))
    {
        puts( "\n No Books in Queue.\n" );
    }
    else
    {
        puts( "Book(s) in Queue Are :" );

        // while not end of queue
        while ( currentPtr != NULL )
        {
            printNode(currentPtr);
            currentPtr = currentPtr->nextPtr;
        }
        puts("End of List");
    }
}

//Print Menu
void instructions( void )
{
    printf ( "\nEnter your choice:\n"
             "   1 to add an item to the queue\n"
             "   2 to remove an item from the queue\n"
             "   3 front of queue\n"
             "   4 back of queue\n"
             "   5 print the queue\n"
             "   6 to end\n" );
}
