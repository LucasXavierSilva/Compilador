#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>


char *names[2] = {"var1", "var2"};
char *types[2] = {"int", "char"};
char *values[2] = {"1", "stephen"};
char *lines[200];
typedef struct {
  char *name;
  char *type;
  char *value;
} symbolTable;

char* RemoveSpaces (char* input);

void InsertSymbol(symbolTable *st, char *name, char *type, char *value);
void AddLine();
void CheckVariables();

int main() {
	setlocale(LC_ALL, "PORTUGUESE");
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
		line = RemoveSpaces(line);
		if(lineN == 0 && !(strstr(line,"programa")))
		{
			printf("O código deve inciar com \"programa\" na linha %i\n",lineN+1);
			break;
		}
		else
		{
			lines[lineN] = line;
    		printf(lines[lineN]);
		}
    	
		lineN++;
	}

    for (i = 0; i < 2; i++)
    {
    	InsertSymbol(&st[i], names[i], types[i], values[i]);
    	printf("\nNome: %s, Tipo: %s, Valor: %s", st[i].name, st[i].type, st[i].value);
    	printf("%p",st[i]);
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
