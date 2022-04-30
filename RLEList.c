#include "RLEList.h"
#include <stdlib.h>

struct RLEList_t
{
    char value;
    int sequence; //number of repetitions of the ASCII value
    RLEList next; //pointer to the next node in the list   
};

//implemention of functions

RLEList RLEListCreate()
{
    RLEList listPtr;
    listPtr = (RLEList) malloc(SIZE_OF_RLEList);
    if(!listPtr) //did memory allocation work
    {
        return NULL;
    }
    //reset struct
    listPtr->value = '\0';
    listPtr->sequence = 0;
    listPtr->next = NULL;
    return listPtr;
}

void RLEListDestroy(RLEList list)
{
    RLEList nextNode = list;
    while(nextNode->next) 
    {
        nextNode = nextNode->next;
        free(list);
        list = nextNode; //initial list to current node
    }
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    //checking the legality of the given parameters
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList currentNode = list;
    while(currentNode->next) //find the final node in the list 
    {
        currentNode = currentNode->next;
    }
    //update the final node (or create one) according to the given value
    if(currentNode->value == value)
    {
        currentNode->sequence++;
        return RLE_LIST_SUCCESS;
    }
    RLEList newNode;
    newNode = (RLEList)malloc(SIZE_OF_RLEList);
    if(!newNode) //did memory allocation work
    {
        return RLE_LIST_OUT_OF_MEMORY;
    } 
    newNode->value = value;
    newNode->sequence++;
    currentNode->next = newNode;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(!list) 
    {
        return LIST_IS_NULL; //-1 if list is NULL
    }
    int counter = 0;
    //going through each node and add to counter its sequence
    RLEList currentNode = list;
    while(currentNode) 
    {
        counter += currentNode->sequence;
        currentNode = currentNode->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    //checking the legality of the given parameters
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0 || index > RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    //find the node at which the character with the given index is
    RLEList currentNode = list;
    RLEList previousNode = list;
    while(index - currentNode->sequence > 0)
    {
        index -= currentNode->sequence;
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    currentNode->sequence--;
    if(!currentNode->sequence)//the node which the value had removed from is empty
    {
        previousNode->next = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    //checking the legality of the given parameters
    if(!list || !result)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(index < 0 || index > RLEListSize(list))
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    //find the node at which the character with the given index is
    RLEList currentNode = list;
    while(index - currentNode->sequence > 0)
    {
        index -= currentNode->sequence;
        currentNode = currentNode->next;
    }
    *result = RLE_LIST_SUCCESS;
    return currentNode->value;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    //checking the legality of the given parameters
    if(!list || !map_function)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    //activating map_funstion on each node value
    RLEList currentNode = list;
    while(currentNode)
    {
        currentNode->value = map_function(currentNode->value);
        currentNode = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    //checking the legality of the given parameters
    if(!list) 
    {
        *result = RLE_LIST_NULL_ARGUMENT; 
        return NULL;  //if list is NULL
    }
    RLEList currentNode = list;
    int nodesNumber = 0;
    while(currentNode)
    {
        nodesNumber ++;
        currentNode = currentNode->next;
    }
    int stringSize = nodesNumber*3*sizeof(char);
    char *RLEListString = (char*)malloc(stringSize);
    if(RLEListString == NULL) //did memory allocation work
    {
        *result = RLE_LIST_ERROR;
        return NULL;
    }
    //creating RLE string which represent the given list
    int index = 0;
    currentNode = list;
    while(index < stringSize)
    {
        RLEListString[index] = currentNode->value;
        index++;
        RLEListString[index] = currentNode->sequence;
        index++;
        RLEListString[index] = '\n';
        index++;
        currentNode = currentNode->next;
    }
    RLEListString[index-1] = '\0';
    *result = RLE_LIST_SUCCESS;
    return RLEListString;
}

