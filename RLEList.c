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

