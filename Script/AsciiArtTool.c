#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdlib.h>

RLEList asciiArtRead(FILE* in_stream)
{
   if(in_stream==NULL)
   {
       return NULL;
   }
   RLEList asciiList = RLEListCreate();
   char currentChar = ' ';
   RLEListResult result;
   do
   {
       currentChar = fgetc(in_stream); //scan a character from file
       if(currentChar == EOF)
       {
           break;
       }
       result = RLEListAppend(asciiList,(char)currentChar);
   } while(result == RLE_LIST_SUCCESS);
   return asciiList;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    char* outString = (char*) malloc(RLEListSize(list)*sizeof(char)+1);
    RLEListResult result = RLE_LIST_NULL_ARGUMENT; //temporary value for result
    for(int index=0; index < RLEListSize(list); index++)
    {
        *(outString+index) = RLEListGet(list,index,&result);
        if(result!=RLE_LIST_SUCCESS)
        {
            free(outString);
            return result;
        }
    }
    *(outString+RLEListSize(list)) = '\0';
    fputs(outString,out_stream);
    free(outString);
    return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result = RLE_LIST_ERROR; //temporary value for result
    char *RLEListString = RLEListExportToString(list, &result);
    if(result != RLE_LIST_SUCCESS)
    {
        return result;
    }
    fputs(RLEListString, out_stream);
    free(RLEListString);
    return RLE_LIST_SUCCESS;
}