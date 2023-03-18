
// Part B Assignment 3
// Create By MHD Rida Tarabishi
//


#include <stdlib.h>
#include <stdio.h>
#include "Book.h"
#include "ctype.h"


//Methods
void removeNewLine(char *array, int size);
bool isValid(long id, int published,char rating);




int main(void)
{
    //initialize head and tail of Queue
    BookQueuePtr headPtr = NULL;
    BookQueuePtr tailPtr = NULL;

    int menuChoice;
    char input[100];

    long id;
    int published;
    char author[100];
    char title[100];
    char rating;

    // display the menu
    instructions();


    fgets(input, sizeof(input), stdin);
    menuChoice = strtol(input,NULL,10);

    while ( menuChoice != 6 )
    {
        switch( menuChoice )
        {
            case 1:
                printf("Enter book Details to add to Stack: \n");
                puts("id: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                id = strtol(input, NULL, 10);

                if(bookExists(headPtr, id)) break;

                puts("Date Published: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                published = strtol(input, NULL, 10);

                //in case numbers are not allowed in Author and title
                //I would loop through characters and check with isDigit

                puts("Author: ");
                fgets(author, sizeof(author), stdin);
                removeNewLine(author, strlen(author));
                input[strcspn(author, "\n")] = '\0';

                puts("Title: ");
                fgets(title, sizeof(title), stdin);
                removeNewLine(title, strlen(title));
                input[strcspn(author, "\n")] = '\0';

                puts("Rating: ");
                rating = toupper(getchar());

                if(!isValid(id, published,rating))
                {
                    puts("Please Try Again");
                    break;
                }

                enqueue(&headPtr, &tailPtr, id,  published,  author,  title, rating);
                printQueue(headPtr);
                break;

            case 2:
                dequeue(&headPtr, &tailPtr, headPtr);
                printQueue(headPtr);
                break;

            case 3:
                front(headPtr);
                break;

            case 4:
                tail(tailPtr);
                break;

            case 5:
                printQueue(headPtr);
                break;

            default:
                puts( "Invalid choice.\n" );
                break;
        }

        fflush(stdin);
        instructions();
        fgets(input, sizeof(input), stdin);
        menuChoice = strtol(input,NULL,10);
    }

}

void removeNewLine(char *array, int size)
{
    if (array[size - 1] == '\n') {
        array[size - 1] = '\0';
    }
}


// to validate user entry
// alternativley I would import POSIX library to make use of regex
bool isValid(long id, int published,char rating)
{

    bool isValid = true;

    //since strtol() Will return zero on fail
    // and to avoid negative id and date
    if(id <=0)
    {
        puts(" ********* Error ********* \n Id must be positve number \n");
        isValid = false;
    }

    // Fixed an issue where this statment was inversed in Part A of the Assignment
    if(isdigit(rating))
    {
        puts(" ********* Error ********* \n Rating must be a Character (A-Z) \n");
        isValid = false;
    }

    if(published<=0)
    {
        puts(" ********* Error ********* \n Published Date must be positve number \n");
        isValid = false;
    }

    return isValid;
}