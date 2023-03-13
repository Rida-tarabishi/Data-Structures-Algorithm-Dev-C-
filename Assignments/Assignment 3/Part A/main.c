
// Part A Assignment 3
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

    ItemPtr stackPtr = NULL;

    int userChoice;
    char input[100];

    long id;
    int published;
    char author[100];
    char title[100];
    char rating;

    instructions();

    fgets(input, sizeof(input), stdin);
    userChoice = strtol(input,NULL,10);

    while (userChoice!=6)
    {
        switch (userChoice)
        {
            case 1:
                printf("Enter book Details to add to Stack: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                id = strtol(input, NULL, 10);

                if(bookExists(stackPtr, id)) break;

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

                if(!isValid(id, published,rating))
                {
                    puts("Please Try Again");
                    break;
                }
                stackPtr = push(stackPtr, id,  published,  author,  title, rating);//push node onto stack
                printStack(stackPtr);//print the stack nodes
                break;
            case 2:
                if(!isEmpty(stackPtr)) stackPtr = pop(stackPtr);
                printStack(stackPtr);
                break;
            case 3:
                !isEmpty(stackPtr) ? topOfStack(stackPtr) : puts("No Books in the Library");
                break;
            case 4:
                !isEmpty(stackPtr) ? bottomOfStack(stackPtr) : puts("No Books in the Library");
                break;
            case 5:
                printStack(stackPtr);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        fflush(stdin);
        instructions();
        fgets(input, sizeof(input), stdin);
        userChoice = strtol(input,NULL,10);
    }

}


void removeNewLine(char *array, int size)
{
    if (array[size - 1] == '\n') {
        array[size - 1] = '\0';
    }
}


// to validate user entry
// alternativley i would import POSIX library to make use of regex
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
    if(!isdigit(rating))
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