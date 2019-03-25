#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpretor.h"

char line[256];
InstrList *instrList;

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");

    while (fgets(line, sizeof(line), fp))
    {
        Instr instr = parser(line);
        printf("%d\n", instr.op);
        //mkList(instr, instrList);
    }

    return EXIT_SUCCESS;
}