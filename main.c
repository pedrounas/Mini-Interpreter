#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpretor.h"

int main(int argc, char *argv[])
{
    char line[256];
    InstrList *InstrList = NULL;

    FILE *fp = fopen(argv[1], "r");

    while (fgets(line, sizeof(line), fp))
    {
        InstrList = mkList(parser(line), InstrList);
    }
    initHashTable();
    run(InstrList);

    return EXIT_SUCCESS;
}