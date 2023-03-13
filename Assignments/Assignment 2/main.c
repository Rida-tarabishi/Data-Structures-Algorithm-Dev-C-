//
// Created by Rida Tarabishi on 2023-02-15.
// MHD Rida Tarabishi : Full Assignment
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// base struct for a book entity
struct Book
    {
        long bookId;
        int bookPublished;
        char bookAuthor[50];
        char bookTitle[100];
        char bookRating;
        struct Book *nextPtr;
    };

    // Structure renaming
    typedef struct Book book;
    typedef struct Book *ItemPtr;

    /*Function Prototypes*/
    void menu ();
    void printList (ItemPtr sPtr);
    ItemPtr makeItem (long id, int published, char author[50], char title[100],char rating);
    ItemPtr removeItem (ItemPtr, long id);
    ItemPtr addItem (ItemPtr sPtr, long id, int published, char author[50], char title[100], char rating);
    void viewItem (ItemPtr sPtr, int id);

    //Added Functions
    void removeNewLine(char *array, int size);
    bool bookExists(ItemPtr sPtr , long id);

int main()
{
    //declarations
    ItemPtr startPtr;  // creating list pointer
    startPtr = NULL;   // initialising the start of the list

    int choice;
    long id;
    int published;
    char author[50];
    char title[100];
    char rating;
    char input[100];

    //Print Menu Prompt
    menu();

    //Temporary
    //scanf ("%d", &choice);

    fgets(input, sizeof(input), stdin);
    choice = strtol(input,NULL,10);

    //loop or exit
    while (choice != 5)
    {
        switch (choice)
        {
            case 1: printf ("\nEnter ID, Published, Author & Title of Book for Insertion: \n");
                //flush stdin for fgets to wait for input, if scanf was previously used
                //fflush (stdin);


                // Altematley I would use a regex to filter user input based on patterns
                // if I was to use POSIX Lib

                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                id = strtol(input, NULL, 10);
                if(bookExists(startPtr, id))
                {
                    puts("Book with the same ID already Exists");
                    break;
                }

                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                published = strtol(input, NULL, 10);

                //in case numbers are not allowed in Author and title
                //I would loop through characters and check with isDigit

                fgets(author, sizeof(author), stdin);
                removeNewLine(author, strlen(author));
                input[strcspn(author, "\n")] = '\0';

                fgets(title, sizeof(title), stdin);
                removeNewLine(title, strlen(title));
                input[strcspn(author, "\n")] = '\0';


                rating = toupper(getchar());
                // regex would be an overkill here since isDigit can deal with the sitiuation
                if(isdigit(rating))
                {
                    puts("Rating must be a Character (A-Z)");
                    break;
                }

                startPtr = addItem (startPtr, id , published , author , title, rating);
                printList (startPtr);
                printf ("\n");
                break;
            case 2:
                printf ("\nEnter Book Id for deletion : ");
                fgets(input, sizeof(input), stdin);
                id = strtol(input, NULL, 10);
                startPtr = removeItem (startPtr, id);
                printList (startPtr);
                printf ("\n");
                break;
            case 3:
                printf ("\nEnter Book ID to View : ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                id = strtol(input, NULL, 10);
                viewItem (startPtr, id);
                printf ("\n");
                break;
            case 4:
                printList (startPtr);
                printf ("\n");
                break;
            default:
                printf ("Invalid Option... Please Try Again \n");
                break;
        }
        fflush (stdin);
        menu ();
        fgets(input, sizeof(input), stdin);
        choice = strtol(input,NULL,10);
    }
    return 0;
}
void menu ()
{
    printf ("\t1: Insert Item into Ordered List\n");
    printf ("\t2: Remove Item from List\n");
    printf ("\t3: View Item from List\n");
    printf ("\t4: Printing the List\n");
    printf ("\t5: Exit\n");
    printf ("\tEnter Choice: ");
}
        //note
        //format used for my reference only
        //id , published , author , title, rating

void printList(ItemPtr sPtr)
{
    ItemPtr tempPtr = sPtr;
    if (tempPtr == NULL)
    {
        puts("The List is Empty... nothing to print");
    }
    else
    {
        printf("ID\tPublished\tAuthor\tTitle\tRating\n");
        while (tempPtr != NULL)
        {
            printf("%ld\t%d\t%s\t%s\t%c\n",tempPtr->bookId,tempPtr->bookPublished,tempPtr->bookAuthor,tempPtr->bookTitle,tempPtr->bookRating);
            tempPtr = tempPtr->nextPtr;
        }
        puts("");
    }
}

void viewItem (ItemPtr sPtr, int id)
{
    ItemPtr prevPtr = NULL, currPtr = sPtr;
    int position = 0;
    if(sPtr == NULL){
        puts("List is empty... Nothing to View...");
    }
    else {
        while(currPtr != NULL && id != currPtr->bookId)
        {
            prevPtr = currPtr;
            currPtr = currPtr->nextPtr;
            position++;
        }
        if (currPtr == NULL)//  node not found
        {
            printf("Book %d was not found in the list", id);
        }
        else // Node found
        {
            printf("Book found at location %d...\n", position+1);
            printf("%ld\t%d\t%s\t%s\t%c\n", currPtr->bookId, currPtr->bookPublished, currPtr->bookAuthor, currPtr->bookTitle, currPtr->bookRating);
        }
    }
}



//Remove Item Method
ItemPtr removeItem (ItemPtr sPtr, long id)
{
    ItemPtr prevPtr = NULL, currPtr = sPtr, tempPtr = NULL;
    if(sPtr == NULL)
    {
        puts("List is empty... Nothing to remove...");
        return sPtr;
    }
    while(currPtr != NULL && id != currPtr->bookId)
    {
        prevPtr = currPtr;
        currPtr = currPtr->nextPtr;
    }
    if (currPtr == NULL)// we have reached the end of the list ... node not found
    {
        printf("Item %ld was not found in the list\n", id);
    }
    else if (prevPtr == NULL) // Node found at the start of the list
    {
        tempPtr = sPtr;
        sPtr = sPtr->nextPtr;
        printf("Item is being deleted...\n"); // inform user
        printf("%ld\t%d\t%s\t%s\t%c\n", tempPtr->bookId, tempPtr->bookPublished, tempPtr->bookAuthor, tempPtr->bookTitle, tempPtr->bookRating);
        free(tempPtr);
    }
    else // Node is found elsewhere in the list
    {
        tempPtr = currPtr;
        prevPtr->nextPtr = currPtr->nextPtr;
        printf("Item is being deleted...\n"); // inform user
        printf("%ld\t%d\t%s\t%s\t%c\n", tempPtr->bookId, tempPtr->bookPublished, tempPtr->bookAuthor, tempPtr->bookTitle,tempPtr->bookRating);
        free(tempPtr);
    }
    return sPtr;
}


//Add item Method
ItemPtr addItem(ItemPtr sPtr, long id, int published, char author[50], char title[100], char rating)
{
    ItemPtr previousPtr, currentPtr, newPtr;
    previousPtr = NULL;
    currentPtr = sPtr;
    newPtr = makeItem(id,published,author,title,rating);

    while (currentPtr != NULL && id > currentPtr->bookId)
    {
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }



    if (previousPtr == NULL) // are we at the start of the list, then insert at start
    {
        newPtr->nextPtr = sPtr;
        sPtr = newPtr;
    }
    else // otherwise we can insert elsewhere
    {
        previousPtr->nextPtr = newPtr;
        newPtr->nextPtr = currentPtr;
    }
    return sPtr;
}


//Make Item Method
ItemPtr makeItem(long id, int published, char author[50], char title[100],char rating)
{
    ItemPtr nPtr =  malloc(sizeof(book));
    if(nPtr == NULL)
    {
        puts("Memory issues... node not created");
    }
    else
    {
        nPtr->bookId = id;
        nPtr->bookPublished = published;
        nPtr->bookRating = rating;
        strcpy(nPtr->bookTitle,title);
        strcpy(nPtr->bookAuthor,author);
        nPtr->nextPtr = NULL;
    }
    return nPtr;
}


//to replace the \n with \0 when using fgets
// to not have it repeated in main multiple times
void removeNewLine(char *array, int size)
{
    if (array[size - 1] == '\n') {
        array[size - 1] = '\0';
    }
}

// i created this method to check whether a book with the same id exists
// implementing as its own method i would not have to go through add method to check
// as it will do error checking on a higher level earlier in the application
// and it can be modified here
// it will return true if more than 0 duplicates exists
bool bookExists(ItemPtr sPtr, long id)
{
    ItemPtr currentPtr = (ItemPtr *) sPtr;
    int counter = 0;
    while (currentPtr != NULL)
    {
        if (currentPtr-> bookId == id){counter++;}
        currentPtr = currentPtr->nextPtr;
    }
    if(counter!=0){return true;}
    return false;
}
