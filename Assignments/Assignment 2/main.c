//
// Created by Rida Tarabishi on 2023-02-15.
// MHD Rida Tarabishi : printList, Menu, Main, viewItem, Struct
//
#include <stdio.h>


// base struct for a book entity
struct Book {
    int bookId;
    int bookPublished;
    char bookAuthor[50];
    char bookTitle[100];
    struct Book *nextPtr;
};

    // Structure renaming
    typedef struct Book book;
    typedef struct Book *ItemPtr;

    /*Function Prototypes*/
    void menu ();
    void printList (ItemPtr sPtr);
    ItemPtr makeItem (int id, int published, char author[50], char title[100]);
    ItemPtr removeItem (ItemPtr, int id);
    ItemPtr addItem (ItemPtr sPtr, int id, int published, char author[50], char title[100]);
    void viewItem (ItemPtr sPtr, int id);

int main(int argc, char *argv[])
{
    //declarations
    ItemPtr startPtr;  // creating list pointer
    startPtr = NULL;   // initialising the start of the list

    int choice, id;
    int published;
    char author;
    char title;

    //Print Prompt
    menu();

    //get input choice used scanf for now.
    scanf ("%d", &choice);

    //loop or exit
    while (choice != 5)
    {
        switch (choice)
        {
            case 1: printf ("\nEnter ID,Price & Name of Item for Insertion: ");
                scanf ("%d%d%s%s", &id,&published,&author, &title);
                startPtr = addItem (startPtr, id , published , &author , &title);
                printList (startPtr);
                printf ("\n");
                break;
            case 2: printf ("\nEnter Item for deletion : ");
                scanf ("%d", &id);
                startPtr = removeItem (startPtr, id);
                printList (startPtr);
                printf ("\n");
                break;
            case 3: printf ("\nEnter Book ID to View : ");
                scanf ("%d", &id);
                viewItem (startPtr, id);
                printf ("\n");
                break;
            case 4: printList (startPtr);
                printf ("\n");
                break;
            default:
                printf ("Invalid Option... Please Try Again \n");
                break;
        }
        menu ();
        scanf ("%d", &choice);
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
//format used for reference only
//id , published , author , title

void printList(ItemPtr sPtr)
{
    ItemPtr tempPtr = sPtr;
    if (tempPtr == NULL)
    {
        puts("The List is Empty... nothing to print");
    }
    else
    {
        printf("ID\tPrice\tName\n");
        while (tempPtr != NULL)
        {
            printf("%d\t%d\t%s\t%s\n", tempPtr->bookId, tempPtr->bookPublished, tempPtr->bookAuthor, tempPtr->bookTitle);
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
            printf("%d\t%d\t%s\t%s\n", currPtr->bookId, currPtr->bookPublished, currPtr->bookAuthor, currPtr->bookTitle);
        }
    }
}



//Remove Item Method


//Add item Method


//Make Item Method


