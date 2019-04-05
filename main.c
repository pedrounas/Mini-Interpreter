#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpretor.h"

int main(int argc, char *argv[])
{
    char line[256];
    char *file;
    file = (char *)malloc(sizeof(char) * 256);
    InstrList *InstrList = NULL;
    printf("Enter the file to be parsed: ");
    scanf("%s", file);
    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("Error: %s does not exist or can't be parsed\n", file);
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), fp))
    {
        InstrList = mkList(parser(line), InstrList);
    }
    initHashTable();
    run(InstrList);

    return EXIT_SUCCESS;
}