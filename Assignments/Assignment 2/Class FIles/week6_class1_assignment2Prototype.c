#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definition
struct item{
   int itemId;
   float itemPrice;
   char itemName[20];
   struct item *nextPtr;
};

// Structure renaming
typedef struct item Item;
typedef struct item *ItemPtr;

/*Function Prototypes*/
void menu ();
void printList (ItemPtr sPtr);
ItemPtr makeItem (int id, float price, char name[20]);
ItemPtr removeItem (ItemPtr, int id);
ItemPtr addItem (ItemPtr sPtr, int id, float price, char name[20]);
void viewItem (ItemPtr sPtr, int id);
 
int main () 
{
  ItemPtr startPtr;  // creating list pointer
  startPtr = NULL;   // initialising the start of the list   
  int id, choice;
  float price;
  char name[20];
  menu ();
  scanf ("%d", &choice);
  while (choice != 5)
  {
    switch (choice)
    {
       case 1: printf ("\nEnter ID,Price & Name of Item for Insertion: ");
               scanf ("%d%f%s", &id,&price,name);
	       startPtr = addItem (startPtr, id,price,name);
	       printList (startPtr);
	       printf ("\n");
	       break;
       case 2: printf ("\nEnter Item for deletion : ");
	       scanf ("%d", &id);
	       startPtr = removeItem (startPtr, id);
	       printList (startPtr);
	       printf ("\n");
               break;
       case 3: printf ("\nEnter Item Number to View : ");
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
  
}// end of main

void menu () 
{
  printf ("\t1: Insert Item into Ordered List\n");
  printf ("\t2: Remove Item from List\n");
  printf ("\t3: View Item from List\n");
  printf ("\t4: Printing the List\n");
  printf ("\t5: Exit\n");
  printf ("\tEnter Choice: ");
} 
 
ItemPtr makeItem(int id, float price, char name[20])
{
   ItemPtr nPtr =  malloc(sizeof(Item)); 
   if(nPtr == NULL)
   {
     puts("Memory issues... node not created");
   }
   else
   {
     nPtr->itemId = id;
     nPtr->itemPrice = price;
     strcpy(nPtr->itemName,name);
     nPtr->nextPtr = NULL;
   }
   return nPtr;
}

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
      printf("%d\t%.2f\t%s\n", tempPtr->itemId, tempPtr->itemPrice, tempPtr->itemName);
      tempPtr = tempPtr->nextPtr;
     }
     puts("");
   }  
}

ItemPtr addItem(ItemPtr sPtr, int id, float price, char name[20])
{
   ItemPtr previousPtr, currentPtr, newPtr;
   previousPtr = NULL;
   currentPtr = sPtr;
   newPtr = makeItem(id,price,name);
   
   while (currentPtr != NULL && id > currentPtr->itemId)
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


ItemPtr removeItem (ItemPtr sPtr, int id)
{
  ItemPtr prevPtr = NULL, currPtr = sPtr, tempPtr = NULL; 
  if(sPtr == NULL)
  {
     puts("List is empty... Nothing to remove...");
     return sPtr;
  }
  while(currPtr != NULL && id != currPtr->itemId)
  {
    prevPtr = currPtr;
    currPtr = currPtr->nextPtr;
  }
  if (currPtr == NULL)// we have reached the end of the list ... node not found
  {
     printf("Item %d was not found in the list\n", id);
  }
  else if (prevPtr == NULL) // Node found at the start of the list
  {
     tempPtr = sPtr;
     sPtr = sPtr->nextPtr;
     printf("Item is being deleted...\n"); // inform user
     printf("%d\t%.2f\t%s\n", tempPtr->itemId, tempPtr->itemPrice, tempPtr->itemName);
     free(tempPtr);
  }
  else // Node is found elsewhere in the list
  {
     tempPtr = currPtr;
     prevPtr->nextPtr = currPtr->nextPtr;
     printf("Item is being deleted...\n"); // inform user
     printf("%d\t%.2f\t%s\n", tempPtr->itemId, tempPtr->itemPrice, tempPtr->itemName); 
     free(tempPtr);
  }
  return sPtr;  
}
void viewItem (ItemPtr sPtr, int id)
{
  ItemPtr prevPtr = NULL, currPtr = sPtr; 
  int position = 0;
  if(sPtr == NULL){
     puts("List is empty... Nothing to View...");
  }
  else {
   while(currPtr != NULL && id != currPtr->itemId)
   {
    prevPtr = currPtr;
    currPtr = currPtr->nextPtr;
    position++;
   }
   if (currPtr == NULL)//  node not found
   {
     printf("Item %d was not found in the list", id);
   }
   else // Node found 
   {
     printf("Item found at location %d...\n", position+1); 
     printf("%d\t%.2f\t%s\n", currPtr->itemId, currPtr->itemPrice, currPtr->itemName);
   }
 }// end of else
}




