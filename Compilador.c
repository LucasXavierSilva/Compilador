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
char *values[2] = {"100", "stephen"};
typedef struct {
  char *name;
  char *type; /* i for int, s for string ... */
  char *value;
} symbolTable;

char* RemoveSpaces (char* input);
void InsertSymbol(symbolTable *st, char *name, char *type, char *value);

int main() {

	symbolTable st[0];
	int lineN = 0;
	//open and get the file handle
	FILE* fh;
	fopen_s(&fh, "test.txt", "r");

	if (fh == NULL){
   		printf("file does not exists %s", "test.txt");
   		return 0;
	}


	//read line by line
	const size_t line_size = 300;
	char* line = malloc(line_size);
	while (fgets(line, line_size, fh) != NULL)  {
		lineN++;
		line = RemoveSpaces(line);
    	printf(line);
	}

    InsertSymbol(&st[0],names[0],types[0],values[0]);
	free(line);    // dont forget to free heap memory
}

char* RemoveSpaces (char* input)
{
    int loop;
    char *output = (char*) malloc (strlen(input));
    char *dest = output;

    if (output)
    {
        for (loop=0; loop<strlen(input); loop++)
            if (input[loop] != ' ')
                *dest++ = input[loop];

        *dest = '\0';
    }
    return output;
}

void InsertSymbol(symbolTable *st, char *name, char *type, char *value)
{
    st->name = name;
    st->type = type;
    st->value = value;
    printf("\n",name);
    printf("\n",type);
    printf("\n",value);
}
