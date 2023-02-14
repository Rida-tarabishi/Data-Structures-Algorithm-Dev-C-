// Codes wriiten on white-board in class

struct item {
    int data;
    struct item *next;
};

typedef struct item Item;
typedef struct item *ItemPtr;

ItemPtr makeItem (int value) 
{
  ItemPtr np = (ItemPtr) malloc (sizeof (Item));
  np->data = value;
  np->next = NULL;
  return np;
}

ItemPtr addItem (ItemPtr sPtr, int value) 
{
  ItemPtr newPtr, currPtr, prevPtr;
  newPtr = makeItem (value);
  prevPtr = NULL;
  currPtr = sPtr;
  while (currPtr != NULL && value > currPtr->data)
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
	  printf ("%d  ", sPtr->data);
	  sPtr = sPtr->next;
	}
     }
}


