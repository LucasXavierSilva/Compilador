#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>

//char wordLst(*word, *nextWord);
/*typedef struct lineLst
{
	char line[200];
	int *nextLine, lineNum;
};

typedef struct wordLst
{
	char word[50];
	int *nxtWord;
} LINES;
*/
char *names[2] = {"var1", "var2"};
char *types[2] = {"int", "char"};
char *values[2] = {"one", "stephen"};
typedef struct {
  char *name;
  char *type;
  char *value;
} symbolTable;

char* RemoveSpaces (char* input);
void InsertSymbol(symbolTable *st, char *name, char *type, char *value);

int main() {

	int i;
	symbolTable st[2];
	int lineN = 0;
	FILE* fh;
	fopen_s(&fh, "test.txt", "r");

	if (fh == NULL){
   		printf("file does not exists %s", "test.txt");
   		return 0;
	}


	//read line by line
	const size_t line_size = 300;
	char* line = malloc(line_size);
	while (fgets(line, line_size, fh) != NULL)
	{
		lineN++;
		line = RemoveSpaces(line);
    	printf(line);
	}

    for (i = 0; i < 2; i++)
    {
    	InsertSymbol(&st[i], names[i], types[i], values[i]);
    	printf("\nNome: %s, Tipo: %s, Valor: %s", st[i].name, st[i].type, st[i].value);
	}
	
	free(line);
}

char* RemoveSpaces (char* input)
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}

void InsertSymbol(symbolTable *st, char *name, char *type, char *value)
{
    st->name = name;
    st->type = type;
    st->value = value;
}
