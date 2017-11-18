#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include <stdbool.h>


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
char *splitChar(char *line, char *firstDelimiter, char *secondDelimiter);
char *splitLine (char *input);
symbolTable *insertSymbol(char *name, char *type, char *value);
void createList(char *name, char *type, char *value);
char checkVariable(char *line);
bool checkVariableList(char *name);
bool dataSearch(symbolTable, char *name);
int checkChar(char *string, char *value);


int main() {
	setlocale(LC_ALL, "PORTUGUESE");
	createList("NULL", "NULL", "NULL");
	int i;
	symbolTable st[2];
	int lineNo = 0;
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
		if(lineNo == 0 && !(strstr(line,"programa")))
		{
			printf("O código deve inciar com \"programa\" na linha %i\n",lineNo+1);
			break;
		}
		else
		{
			lines[lineNo] = line;
    		//printf(lines[lineNo]);
    		checkVariable(lines[lineNo]);
    		splitLine(line);
		}
    	
		lineNo++;
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
        if (input[i]!=' ' && input[i] != '\t' && input [i] != '\n')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}

char *splitChar(char *line, char *firstDelimiter, char *secondDelimiter)
{
    const char *s = line;

	const char *PATTERN1 = firstDelimiter;
    const char *PATTERN2 = secondDelimiter;

    char *target = NULL;
    char *start, *end;

	/*
	if(strstr(s,"\""))
	{
		PATTERN1 = "\"";
		PATTERN2 = "\"";
	}*/
	
    if ( start = strstr( s, PATTERN1 ) )
    {
        start += strlen( PATTERN1 );
        if ( end = strstr( start, PATTERN2 ) )
        {
            target = ( char * )malloc( end - start + 1 );
            memcpy( target, start, end - start );
            target[end - start] = '\0';
			return target;
            
        }
        else
        {
        	printf("Delimitador %s não encontrado", PATTERN2);
        	return 0;
		}
    }

    //if ( target ) printf( "\n\n\n %s\n\n\n", target );
}

char *splitLine (char *input)
{
	char *token, *string, *name="NULL", *type="NULL", *value="NULL", splitVariable[100], splitValue[100];
	
	strcpy(splitVariable, input);
	strcpy(splitValue, input);
	
	if(strstr(input,"inteiro"))
	{
		type = "inteiro";
	}
	else if(strstr(input,"caractere"))
	{
		type = "caractere";
	}
	else if(strstr(input,"real"))
	{
		type = "real";
	}
	else
	{
		printf("\nNão é uma declaração de variável!\n");
		return 0;
	}
	printf("TESTE!!");
	if(strstr(input,"#"))
	{		
	    name = splitChar(splitVariable,"#",",");
	    printf("SACA ESSE NOME!: %s",name);
	}

	if(strstr(input,"="))
	{
		name = splitChar(splitVariable,"#", "=");
	  	value = splitChar(splitValue,"\"","\"");       
	}
	
	else
	{
	   	name = strtok(splitVariable, "=");
		value = "NULL";
	}
	insertSymbol(name, type, value);
	return token;
}

symbolTable *insertSymbol(char *name, char *type, char *value)
{
	symbolTable *st;
	st = (symbolTable*)malloc(sizeof(symbolTable));
	
    st->name = (char *)malloc(strlen(name));
    strncpy(st->name, name, strlen(name)+1);
    
    st->type = (char *)malloc(strlen(type));
    strncpy(st->type, type, strlen(type)+1);
    
    st->value = (char *)malloc(strlen(value));
    strncpy(st->value, value, strlen(value)+1);
    st->next = NULL;
    
    printf("\n Nome: %s, Tipo: %s, Valor: %s Insert into table Successful!\n",name, type, value);
    return st;
}

void createList(char *name, char *type, char *value)
{
	root = insertSymbol(name, type, value);
}


void checkLine(char *line, int lineNo)
{
	
}

char checkVariable(char *line)
{
	
	int aux = 0, x;
    while(!isspace(line[aux]))
    {
        aux++;
    }
    char *variable = (char*) malloc(sizeof(char)*aux);
    for(x=0;x!=aux;x++)
    {
        variable[x] = line[x];
    }
    return variable;
}

bool checkVariableList(char *name)
{
	bool b;
}


bool dataSearch(symbolTable st, char *name)
{    bool found = false;

	return found;
}

int checkChar(char *string, char *value)
{
	const char *invalidChars = value;
					   char *mystring = string;
					   char *character = mystring;
					   int i = 0;
					   while (*character)
					   {
					       if (strchr(invalidChars, *character))
					       {
					         i++;
					       }					
					       character++;
					   }
					   printf("\n\n %i \n\n",i);
		return i;
}
