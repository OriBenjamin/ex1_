#include "RLEList.h"

struct RLEList_t{
    //TODO: implement
    char value;
    int sequence; //number of repetitions of the ASCII value
    RLEList_t* next; //pointer to the next node in the list   
};

//implement the functions here

RLEList RLEListCreate()
{
    RLEList list_p; //pointer to list
    if(!(list_p = (RLEList) malloc(SIZE_OF_RLEList))) return NULL; //did memory alocation work
    // RLEList_t list = *list_p;
    (*list_p).value = NULL; //reset struct
    (*list_p).sequence = 0;
    (*list_p).next = NULL;
    return list_p;
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
    RLEList CurrNode = list->next;
    while(CurrNode)
    {
        CurrNode = CurrNode->next;
    }
    RLEList NewNode;
    if(!(NewNode = (RLEList) malloc(SIZE_OF_RLEList))) return RLE_LIST_OUT_OF_MEMORY;
    NewNode->value = value;
    CurrNode->next = NewNode;
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
    int counter = index;
    RLEList CurrNode = list->next;
    while(counter != 0)
    {
        CurrNode = CurrNode->next;
        counter--;
    }
    CurrNode->next = NULL;
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result);
{
    if(&list == NULL || index == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0 || index > RLEListSize(list))
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int counter = index;
    RLEList CurrNode = list->next;
    while(counter != 0)
    {
        CurrNode = CurrNode->next;
        counter--;
    }
    ???????????if(CurrNode->next)
    {
        *result = RLE_LIST_SUCCESS;
    }
    else
    {
        return 0;
    }
    return CurrNode->next;
}


