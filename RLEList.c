#include "RLEList.h"

struct RLEList_t
{
    char value;
    int sequence; //number of repetitions of the ASCII value
    RLEList_t* next; //pointer to the next node in the list   
};

//implemention of functions

RLEList RLEListCreate()
{
    RLEList listPtr; //pointer to list
    listPtr = (RLEList) malloc(SIZE_OF_RLEList);
    if(!listPtr)
    {
        return RLE_LIST_OUT_OF_MEMORY; //did memory alocation work
    }
    // RLEList_t list = *listPtr;
    listPtr->value = NULL; //reset struct
    listPtr->sequence = 0;
    listPtr->next = NULL;
    return listPtr;
}

void RLEListDestroy(RLEList list)
{
    free(list);
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if(&list == NULL || value == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList currentNode = list->next;
    while(currentNode->next)
    {
        currentNode = currentNode->next;
    }
    if(currentNode->value == value)
    {
        currentNode->sequence++;
        return RLE_LIST_SUCCESS;
    }
    RLEList newNode;
    newNode = (RLEList) malloc(SIZE_OF_RLEList))
    if(!newNode)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    } 
    newNode->value = value;
    currentNode->next = newNode;
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(&list == NULL || index == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0 || index > RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList currentNode = list;
    RLEList previousNode = list;
    while(index - currentNode->sequence > 0)
    {
        index -= currentNode->sequence;
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    currentNode->sequence--;
    if(!currentNode->sequence)
    {
        previousNode->next = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result);
{
    if(&list == NULL || index == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(index < 0 || index > RLEListSize(list))
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    RLEList currentNode = list;
    while(index - currentNode->sequence > 0)
    {
        index -= currentNode->sequence;
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    return currentNode->value;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(&list == NULL || map_function == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList currentNode = list;
    while(currentNode)
    {
        currentNode->value = *map_function(currentNode->value);
        currentNode = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}


