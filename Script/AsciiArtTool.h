//
// Created by Ori Dekel on 24/04/2022.
//

#ifndef ASCII_ART_TOOL_H
#define ASCII_ART_TOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

/*scanning a source file and return RLEList which represent its content.
returns NULL if the given file is NULL*/
RLEList asciiArtRead(FILE* in_stream);

/*making ASCII picture file from a given RLEList which represent the list's value.
returns RLE_LIST_SUCCESS if the the file preparation process succeeded
returns RLE_LIST_NULL_ARGUMENT if one of the given parameters is NULL*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/*making encoded RLEList string which represnt an ASCII picture file.
writing the RLEList data into a destination file.
returns RLE_LIST_SUCCESS if the the encoding and writing processes succeeded
returns RLE_LIST_NULL_ARGUMENT if one of the given parameters is NULL*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);





#endif // ASCII_ART_TOOL_H