#include "AsciiArtTool.h"

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
    return 0;
}
int main(int argc, char** argv)
{
    char* flag = *(argv+1);
    char flagKind = *(flag+1); 
    const char* sourceFileName = *(argv+2)
    char* targetFileName = *(argv+3)
    RLEListResult RLEOperationsResult = RLE_LIST_ERROR;
    File* sourceFile = fopen(sourceFileName,'r');
    File* targetFile = fwrite(targetFileName,'w');
    RLEList asciiRLEList = asciiArtRead(sourceFile);
    if(flagKind=='e')
    {
        RLEOperationsResult = asciiArtPrintEncoded(asciiRLEList,targetFile);
        if(RLEOperationsResult != RLE_LIST_SUCCESS)
        {
            RLEListDestroy(asciiRLEList);
            return RLEOperationsResult;
        }
    }
    else if(flagKind=='i')
    {
        RLEOperationsResult = RLEListMap(asciiRLEList, invertChar);
        if(RLEOperationsResult != RLE_LIST_SUCCES)
        {
            RLEListDestroy(asciiRLEList);
            return RLEOperationsResult;
        }
        asciiArtPrint(asciiRLEList,targetFile);
    }
    RLEListDestroy(asciiRLEList);
    return RLEOperationsResult;
}