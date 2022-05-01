#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>
#include <stdio.h>

char invertChar(char c) //from type MapFunction
{
    if(c == '@')
    {
        return ' ';
    }
    else if(c == ' ')
    {
        return '@';
    }
    return c;
}
int main(int argc, char** argv)
{
    //getting the input from the command line
    char* flag = *(argv+1);
    char flagKind = *(flag+1);  
    const char* sourceFileName = *(argv+2);
    char* targetFileName = *(argv+3);
    RLEListResult RLEOperationsResult = RLE_LIST_ERROR; //temporary value for RLEOperationsResult
    //open source and target files for reading and writing
    const char* readFlag = "r";
    const char* writeFlag = "w";
    FILE* sourceFile = fopen(sourceFileName,readFlag);
    FILE* targetFile = fopen(targetFileName,writeFlag);
    RLEList asciiRLEList = asciiArtRead(sourceFile);
    /*making encoded RLEList string which represnt the source file ASCII picture.
    put it in the target file*/
    if(flagKind == 'e')
    {
        RLEOperationsResult = asciiArtPrintEncoded(asciiRLEList,targetFile);
        if(RLEOperationsResult != RLE_LIST_SUCCESS)
        {
            RLEListDestroy(asciiRLEList);
            fclose(sourceFile);
            fclose(targetFile);
            return RLEOperationsResult;
        }
    }
    else if(flagKind=='i') //invert the source file ASCII picture and put it in the target file
    {
        RLEOperationsResult = RLEListMap(asciiRLEList, invertChar);
        if(RLEOperationsResult != RLE_LIST_SUCCESS)
        {
            RLEListDestroy(asciiRLEList);
            fclose(sourceFile);
            fclose(targetFile);
            return RLEOperationsResult;
        }
        asciiArtPrint(asciiRLEList,targetFile);
    }
    RLEListDestroy(asciiRLEList);
    fclose(sourceFile);
    fclose(targetFile);
    return RLEOperationsResult;
}