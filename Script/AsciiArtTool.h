//
// Created by Ori Dekel on 24/04/2022.
//

#ifndef ASCII_ART_TOOL_H
#define ASCII_ART_TOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream);

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);





#endif // ASCII_ART_TOOL_H