#define HASH_SIZE 20
#define MULTIPLIER 31

typedef enum
{
   ATRIB,
   ADD,
   SUB,
   MUL,
   DIV,
   IF_I,
   PRINT,
   READ,
   GOTO_I,
   LABEL,
   QUIT
} OpKind;

typedef enum
{
   EMPTY,
   INT_CONST,
   STRING
} ElemKind;

typedef struct
{
   ElemKind kind;
   union {
      int val;
      char *name;
   } contents;
} Elem;

typedef struct
{
   OpKind op;
   Elem first, second, third;
} Instr;

typedef struct List
{
   char *key;
   int value;
   struct List *next;
} List;

typedef struct _InstrList
{
   Instr instr;
   struct _InstrList *next;
} InstrList;

List *table[HASH_SIZE];
InstrList *instrList;

Instr parser(char *line);

Elem mkVar(char *s);
Elem mkInt(int x);
Instr mkInstr(OpKind op, Elem x, Elem y, Elem z);
InstrList *mkList(Instr instr, InstrList *instrList);

Instr makeReadInstr(char *line);
Instr makeWriteInstr(char *line);
Instr makeIfInstr(char *line);
Instr makeGotoInstr(char *line);
Instr makeJumpInstr(char *line);
Instr makeLabelInstr(char *line);
Instr makeAtribInstr(char *line);
Instr makeQuitInstr();

void read(char line[]);
void write(char line[]);
void init();
unsigned int hash(char *str);
List *lookup(char *key);
void insert(char *key, int value);

/*Auxiliary functions declaration*/
char *extractVarName(char *line, char initialDelimitator, char finalDelimitator);
char *extractLabelName(char *line);