#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpretor.h"

Instr parser(char *line)
{
    if (line == NULL)
    {
        printf("Error in parser: NULL line!\n");
        exit(EXIT_FAILURE);
    }
    //FAZER DA FORMA mkInstr(ADD, mkVar("x"), mkInt(2), mkInt(3));
    //void run(InstrList l)
    // Elem mkVar(char *s);
    // Elem makeIfInstr(int x);
    // Instr makeIfInstr(OpKind op, Elem x, Elem y, Elem z);
    // IList makeLabelInstr(Instr head, IList tail);

    Instr instr;

    if (strncmp("ler", line, strlen("ler")) == 0)
    {
        char *name = extractVarName(line, '(', ')');
        instr.op = READ;
        instr.first.contents.name = name;
        instr.first.kind = STRING;
        return instr;
    }
    else if (strncmp("escrever", line, strlen("escrever")) == 0)
    {
        char *name = extractVarName(line, '(', ')');
        instr.op = PRINT;
        instr.first.contents.name = name;
        instr.first.kind = STRING;
        return instr;
    }
    else if (strncmp("if", line, strlen("if")) == 0)
    {
        char *name = extractVarName(line, '(', ')');
        char *label = extractLabelName(line);
        Instr instr;
        instr.op = IF_I;
        instr.first.contents.name = name;
        instr.first.kind = STRING;

        return instr;
    }
    else if (strncmp("goto", line, strlen("goto")) == 0)
    {
        char *label = extractLabelName(line);
        instr.op = GOTO_I;
        instr.first.kind = STRING;
        instr.first.contents.name = label;
        return instr;
    }
    else if (strncmp("label", line, strlen("label")) == 0)
    {
        char *label = extractLabelName(line);
        instr.op = LABEL;
        instr.first.kind = STRING;
        instr.first.contents.name = label;
        return instr;
    }
    else if (strstr(line, "="))
    {
        char *aux = (char *)malloc(sizeof(char) * 2);
        char *elements[5];
        aux = strtok(line, " ");
        int i = 0;

        while (aux != NULL)
        {
            char *p = (char *)malloc(strlen(aux) + 1);
            strcpy(p, aux);
            elements[i] = p;
            aux = strtok(NULL, " ");
            i++;
        }
        // for (i = 0; i < 5; i++)
        // {
        //     printf("ELEMENT %d -> %s\n", i, elements[i]);
        // };

        char op = *elements[3];

        switch (op)
        {
        case '+':
            instr.op = ADD;
            break;
        case '-':
            instr.op = SUB;
            break;
        case '*':
            instr.op = MUL;
            break;
        case '/':
            instr.op = DIV;
            break;

        default:
            break;
        }
        instr.first.kind = INT_CONST;
        instr.first.contents.val = atoi(elements[0]);

        instr.second.kind = INT_CONST;
        instr.second.contents.val = atoi(elements[2]);

        instr.third.kind = INT_CONST;
        instr.third.contents.val = atoi(elements[4]);

        return instr;
    }
    else if (strncmp("quit", line, strlen("quit") + 1))
    {
        exit(EXIT_SUCCESS);
    }
    
    else
    {
        printf("Error in parser: Instruction \"%s\"not recognized!\n", line);
        exit(EXIT_FAILURE);
    }

    return instr;
}

Instr *makeReadInstr(char *line)
{
    char *name = extractVarName(line, '(', ')');

    Instr *instr = (Instr *)malloc(sizeof(Instr));

    instr->op = READ;
    instr->first.kind = STRING;
    instr->first.contents.name = name;

    return instr;
}

Instr *makeWriteInstr(char *line)
{
    char *name = extractVarName(line, '(', ')');

    Instr *instr = (Instr *)malloc(sizeof(Instr));

    instr->op = PRINT;
    instr->first.kind = STRING;
    instr->first.contents.name = name;

    return instr;
}

Instr *makeIfInstr(char *line)
{
}

Instr *makeGotoInstr(char *line)
{
}

Instr *makeJumpInstr(char *line)
{
}

Instr *makeLabelInstr(char *line)
{
}

Instr *makeAtribInstr(char *line)
{
}

Instr *makeQuitInstr()
{
}

void read(char line[])
{

    // char *var;
    // var = parser(line);
    // Instr* x = malloc(sizeof(Instr));
    // x->op = READ;
    // x->first.kind = EMPTY;
    // x->first.contents.name = var;

    // insert(var,0);
}

void write(char line[])
{
    // char *var;
    // var = parser(line);
    // printf("%d\n",lookup(var)->value);
}

void init()
{
    memset(table, 0, sizeof(HASH_SIZE));
}

unsigned int hash(char *str)
{
    unsigned int h;
    unsigned char *p;
    h = 0;
    for (p = (unsigned char *)str; *p != '\0'; p++)
    {
        h = MULTIPLIER * h + *p;
    }
    return h % HASH_SIZE;
}

List *lookup(char *key)
{
    int index = (int)hash(key);
    List *aux = table[index];
    while (aux != NULL)
    {
        if (!strcmp(key, aux->key))
        {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void insert(char *key, int value)
{
    int val = (int)hash(key);
    List *aux = (List *)malloc(sizeof(List));
    aux->key = key;
    aux->value = value;
    aux->next = table[val];
    table[val] = aux;
}

/*Auxiliary functions definitions*/
char *extractVarName(char *line, char initialDelimitator, char finalDelimitator)
{
    char *aux = (char *)malloc(sizeof(char) * 256);
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == initialDelimitator)
        {
            int j = i + 1;
            int count = 0;
            while (line[j] != finalDelimitator)
            {
                j++;
                count++;
            }
            strncpy(aux, line + i + 1, count);
            break;
        }
    }

    return aux;
}

char *extractLabelName(char *line)
{
    char *aux = (char *)malloc(sizeof(char) * 2);
    char p = line[sizeof(line) - 2];
    aux[0] = p;
    p = line[sizeof(line) - 1];
    aux[1] = p;

    return aux;
}