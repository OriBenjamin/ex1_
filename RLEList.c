#include "RLEList.h"
#include <stdlib.h>

struct RLEList_t
{
    RLEList next; //pointer to the next node in the list   
    int sequence; //number of repetitions of the ASCII value
    char value;
};

//implemention of functions

RLEList RLEListCreate()
{
    
    RLEList listPtr;
    listPtr = (RLEList) malloc(SIZE_OF_RLEList);
    //printf("'%zu, %zu, %zu'\n",sizeof(*listPtr),sizeof(int),sizeof(char));
    //SIZE_OF_RLEList
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
    if(!list)
    {
        return;
    }
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
    if(!list||value=='\0')
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->value=='\0') //initializing the first node
    {
        list->value = value;
        list->sequence++;
        return RLE_LIST_SUCCESS;
    }
    RLEList currentNode = list;

    while(currentNode->next) //find the final node in the list 
    {
        currentNode = currentNode->next;
    }
    //update the final node (or create one) according to the given value
    if(currentNode->value == value)
    {
        (currentNode->sequence)++;
        return RLE_LIST_SUCCESS;
    }

    RLEList newNode = RLEListCreate();
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
    if(index < 0 || index >= RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    //find the node at which the character with the given index is
    RLEList currentNode = list;
    RLEList previousNode = list;
    while((index+1) - currentNode->sequence > 0)
    {
        index -= currentNode->sequence;
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    currentNode->sequence--;
    RLEList temporaryNext = NULL;
    if(!currentNode->sequence)//the node which the value had removed from is empty
    {
        if(currentNode == previousNode) //if removed node is at the beginning of list
        {
            if(!currentNode->next) //only one node in list
            {
                currentNode->value = '\0';
                currentNode->sequence = 0;
                return RLE_LIST_SUCCESS;
            }
            while(currentNode->next) 
            {
                currentNode->value = currentNode->next->value;
                currentNode->sequence = currentNode->next->sequence;
                if(!currentNode->next||!currentNode->next->next)
                {
                    free(currentNode->next);
                    currentNode->next = NULL; 
                    break;
                }
                currentNode = currentNode->next;
            }
        } else 
        {
            previousNode->next = currentNode->next;
            free(currentNode);
            if(previousNode->next&&previousNode->value==previousNode->next->value)
            {
                previousNode->sequence += previousNode->next->sequence;
                temporaryNext = previousNode->next;
                previousNode->next = previousNode->next->next;
                free(temporaryNext);
            }
        }
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    //checking the legality of the given parameters
    if(!list)
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return '\0';
    }
    if(index < 0 || index >= RLEListSize(list))
    {
        if(result)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return '\0';  
    }
    //find the node at which the character with the given index is
    RLEList currentNode = list;
    while((index+1) - currentNode->sequence > 0)
    {
        index -= currentNode->sequence;
        currentNode = currentNode->next;
    }
    if(result)
    {
        *result = RLE_LIST_SUCCESS;
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
    RLEList temporaryNext = NULL;
    while(currentNode)
    {
        currentNode->value = map_function(currentNode->value);
        while(currentNode->next&&currentNode->value==map_function(currentNode->next->value))
        {
            currentNode->sequence += currentNode->next->sequence;
            temporaryNext = currentNode->next;
            currentNode->next = currentNode->next->next; 
            free(temporaryNext);
        }
        currentNode = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    //checking the legality of the given parameters
    if(!list) 
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT; 
        }
        return NULL;  //if list is NULL
    }
    RLEList currentNode = list;
    int nodesNumber = 0;
    while(currentNode)
    {
        nodesNumber ++;
        currentNode = currentNode->next;
    }
    
    int stringSize = 0;
    currentNode = list;
    while(currentNode)
    {
        stringSize += 2 + snprintf(NULL,0 ,"%d",currentNode->sequence);
        currentNode=currentNode->next;
    }
    
    char *RLEListString = (char*)malloc(stringSize+1);
    
    if(RLEListString == NULL) //did memory allocation work
    {
        if(result)
        {
            *result = RLE_LIST_ERROR;
        }
        return NULL;
    }
    //creating RLE string which represents the given list
    int index = 0;
    currentNode = list;
    
    int currentSequenceLength = 0;
    while(index < stringSize)
    {
        RLEListString[index] = currentNode->value;
        index++;
        currentSequenceLength = snprintf(NULL,0 ,"%d",currentNode->sequence);
        snprintf(RLEListString+index,currentSequenceLength+1,"%d",currentNode->sequence);
        index+=currentSequenceLength;
        RLEListString[index] = '\n';
        index++;
        currentNode = currentNode->next;
    }
    RLEListString[index] = '\0';
    if(result)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return RLEListString;
}

