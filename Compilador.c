#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>


char *names[2] = {"var1", "var2"};
char *types[2] = {"int", "char"};
char *values[2] = {"1", "stephen"};
char *lines[200];
typedef struct list {
  char *name;
  char *type;
  char *value;
  struct list *next;
} symbolTable;
symbolTable *root = NULL; 

char *removeSpaces (char *input);

symbolTable insertSymbol(char *name, char *type, char *value);
void createList(char *name, char *type, char *value);
void addLine();
void checkVariables();

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
		line = removeSpaces(line);
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
/*
    for (i = 0; i < 2; i++)
    {
    	insertSymbol(names[i], types[i], values[i]);
    	printf("\nNome: %s, Tipo: %s, Valor: %s", st[i].name, st[i].type, st[i].value);
    	printf("%p",st[i]);
	}
	*/
	free(line);
	free(root);
}

char* removeSpaces (char* input)
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

symbolTable insertSymbol(char *name, char *type, char *value)
{
	symbolTable *st;
	st = (symbolTable*)malloc(sizeof(symbolTable));
	
    st->name = (char *)malloc(strlen(name));
    strncpy(st->name, name, strlen(name)+1);
    
    st->type = (char *)malloc(strlen(type));
    strncpy(st->type, type, strlen(type)+1);
    
    st->value = (char *)malloc(strlen(value));
    strncpy(st->value, value, strlen(value)+1);
    
    return *st;
}

void CreateList(char *name, char *type, char *value)
{
	*root = insertSymbol(name, type, value);
}
