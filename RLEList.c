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
    RLEList listPtr;
    listPtr = (RLEList) malloc(SIZE_OF_RLEList);
    if(!listPtr) //did memory allocation work
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    //reset struct
    listPtr->value = NULL;
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
    RLEList currentNode = list->next;
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
    newNode = (RLEList) malloc(SIZE_OF_RLEList))
    if(!newNode) //did memory allocation work
    {
        return RLE_LIST_OUT_OF_MEMORY;
    } 
    newNode->value = value;
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
    while(list) 
    {
        counter += list->sequence;
        list = list->next;
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

char RLEListGet(RLEList list, int index, RLEListResult *result);
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
        currentNode->value = *map_function(currentNode->value);
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
        return NULL;  //NULL if list is NULL
    }
    int stringSize = RLEListSize(list)*3*sizeof(char);
    char* string = (char*)malloc(stringSize+1);
    if(string == NULL) //did memory allocation work
    {
        *result = RLE_LIST_ERROR;
        return NULL;
    }
    //creating RLE string which represent the given list
    char* current = string;
    while(list) 
    {
        *current = list->value;
        current++;
        *current = list->sequence;
        current++;
        *current = '\n';
        current++;
        list = list->next;
    }
    *result = RLE_LIST_SUCCESS;
    return string;
}

