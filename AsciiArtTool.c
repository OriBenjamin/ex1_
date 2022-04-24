#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream)
{
   RLEList artList = RLEListCreate();
   char current = '';
   do
   {
       fgets(&current,1,in_stream); // scan character from file 
       RLEListAppend(artList,current);
   }while(current!=NULL);
  
   return artList;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
   char current = '';
   int index = 0;
   RLEListResult result; // = 0?
   do
   {
       current = RLEListGet(list,index++,&result);
       if(result != SUCCESS_LIST_RLE)
       {
           return result;
       }
       fputs(&current,out_stream); // put characters in file 
   }while(current!=NULL);
   return SUCCESS_LIST_RLE;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult  result; // = 0?
    int listSize = RLEListSize(list);
    fputs(RLEListExportToString(list,result),out_stream);
    return SUCCESS_LIST_RLE;
}