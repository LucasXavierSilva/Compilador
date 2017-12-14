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
  char *sizeLimit;
  struct list *next;
} symbolTable;
symbolTable *root = NULL, *leaf = NULL; 

char *removeSpaces (char *input);
char *splitChar(char *line, char *firstDelimiter, char *secondDelimiter);
char *splitLine (char *input);
symbolTable *insertSymbol(char *name, char *type, char *value, char *sizeLimit);
void createList(char *name, char *type, char *value, char *sizeLimit);
void printList();
int checkInsertVarName(char *name);
char checkVariable(char *line);
bool checkVariableList(char *name);
bool dataSearch(symbolTable, char *name);
int checkChar(char *string, char *value);
int *checkList(char *name);
int checkNumber(const char *string);
int testReserved(char *str);
int testSemi(const char *str); 

int size = 0;

int main() {
	setlocale(LC_ALL, "PORTUGUESE");
	int i;
	int lineNo = 0;
	FILE* fh;
	fopen_s(&fh, "test.txt", "r");

	if (fh == NULL){
   		printf("O seguinte arquivo não existe: %s", "test.txt");
   		system("pause");
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
			system("pause");
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
	
	char name = "teste";
    printList();
	printf("\nQuantidade de bytes usado: %i",size);
	free(line);
	free(root);
}

//Remove spaces and useless data
char* removeSpaces (char* input)
{
    int i,j, aux = 1;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
    	if(input[i] == '\"' )
        {
        	aux = aux*(-1);
		}
        if ((input[i] != ' ' && input[i] != '\t' && input [i] != '\n') || (aux < 0))
		{    
            output[j]=input[i];
		}                      
        else
        {
            j--;
		}                                 
    }
    output[j]=0;
    return output;
}

//Split the characters by the given delimiter
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
        	target = "ERRO Delimitador não encontrado";
        	return target;
		}
    }

    //if ( target ) printf( "\n\n\n %s\n\n\n", target );
}

//Splits the contents in the line
char *splitLine (char *input)
{
	char *token, *string, *name="NULL", *type="NULL", *value="NULL", *sizeLimit="NULL", splitVariable[strlen(input)], splitValue[strlen(input)];
	strcpy(splitVariable, input);
	strcpy(splitValue, input);
	int aux = checkChar(input,"#");
	
	if(strstr(input,"inteiro") || strstr(input,"caractere") || strstr(input,"real"))
	{
		if(strstr(input,"#"))
		{
		
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
			printf("Atribuição de variável deve receber tipo de valor inteiro, caractere ou real!");
			system("pause");
		}
		
		if(testSemi(input))
		{
			printf("\nA linha deve finalizar com \";\"");
			return 0;
		}
		
		while(aux != 0)
		{
			value = "NULL";
			name = "NULL";
			sizeLimit = "NULL";
			if(strstr(input,"#"))
			{	
				if(!strstr(splitChar(input,"#",","),"ERRO"))
			    	name = splitChar(input,"#",",");
			    else if(!strstr(splitChar(input,"#",";"),"ERRO"))
			    	name = splitChar(input,"#",";");
			}
			if(strstr(input,"="))
			{
				if(!strstr(splitChar(input,"#","="),"ERRO"))
				{
					name = splitChar(input,"#", "=");	
				}
					
				if(!strstr(splitChar(input,"=",","),"ERRO"))
			  		value = splitChar(input,"=",",");
			  
				if(!strstr(splitChar(input,"=",";"),"ERRO"))
			  		value = splitChar(input,"=",";");
			  	
				if(type != "caractere" && strstr(input,"\""))
				{
					printf("\nTipo %s não pode receber valor do tipo charactere!", type);
					return 0;
				}
				else if(type == "caractere" && strstr(input,"\""))
			  		value = splitChar(splitValue,"\"","\"");
			}		
			
			if(strstr(input,"["))
			{
				sizeLimit = splitChar(input,"[","]");
				if(!strstr(splitChar(input,"[","]"),"ERRO") && checkNumber(sizeLimit) == 1)
				{
					name = splitChar(input,"#","[");
				}
				else if(checkNumber(sizeLimit) == 0)
				{
					printf("\nO campo aceita apenas valores numéricos entre \"[\" e \"]\".");
					return 0;
				}
			}
			if(aux > 1)
			{
				input = splitChar(input,",",";");
				strcat(input, ";");
			}
			if(value != "NULL" && strlen(value) > atoi(sizeLimit) && sizeLimit != "NULL")
			{
				printf("\nO valor %s é maior do que o limite implicado de [%s]", value, sizeLimit);
			}
			/*
			if(checkList(name) == 1)
			{
				printf("Nome já existe na tabela de símbolos: %s", nome);
				return 0;
			}*/
			
			testReserved(name);
    		checkInsertVarName(name);
			insertSymbol(name, type, value, sizeLimit);
			aux--;
		}

	}	
	
	}
	else
	{
		//printf("\nNão é uma declaração de variável!\n");
		return 0;
	}
	return token;
}
//Inserts variables into the Symbol Table
symbolTable *insertSymbol(char *name, char *type, char *value, char *sizeLimit)
{	
	if (root == NULL)
	{
		root = (symbolTable *) malloc(sizeof(symbolTable));	  
		leaf = root;
	}
		
	else 
	{
		leaf->next = (symbolTable *) malloc(sizeof(symbolTable));
		leaf = leaf->next;
	}
	leaf->name = (char *)malloc(strlen(name));
    strncpy(leaf->name, name, strlen(name)+1);
    
    leaf->type = (char *)malloc(strlen(type));
    strncpy(leaf->type, type, strlen(type)+1);
    
    leaf->value = (char *)malloc(strlen(value));
    strncpy(leaf->value, value, strlen(value)+1);
    
    leaf->sizeLimit = (char *)malloc(strlen(sizeLimit));
    strncpy(leaf->sizeLimit, value, strlen(sizeLimit)+1);
    leaf->next == NULL;
    
    size = size + sizeof(leaf->name);
    size = size + sizeof(leaf->value);
    size = size + sizeof(leaf->type);
    size = size + sizeof(leaf->sizeLimit);
    size = size + sizeof(leaf);
    //printf("\n Nome: %s, Tipo: %s, Valor: %s Insert into table Successful!\n",name, type, value);
    return leaf;
}

//Creates a list
void createList(char *name, char *type, char *value, char *sizeLimit)
{
	root = insertSymbol(name, type, value, sizeLimit);
}

//Prints all the contents in the list
void printList()
{
    	
    symbolTable *aux;
    int i=1;
       
    aux = root;
      
	while (aux != NULL) 
	{
       printf("\n%iª Variável Nome: %s Tipo: %s Valor: %s",i, aux->name, aux->type, aux->value);
       i++;
       aux = aux->next; /* próxima célula */
    }
    free(aux);
}

//Verifies if the variable is already inserted
int checkInsertVarName(char *name)
{
	symbolTable *st = (symbolTable *) malloc(sizeof(symbolTable));
	//char *auxC = "teste";
	int i = 1;
	st = root;
	
	while(st != NULL && st->name != NULL)
	{	
		if(strcmp(name,st->name) == 0)
		{
			printf("\nVariável de nome \"%s\" já foi inserido:\n",st->name);
			system("pause");
		}
		else
		{
			st = st->next;
		}
	}
	
	free(st);
}

//Check the variable value
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

//Checks the Variable's List
bool checkVariableList(char *name)
{
	bool b;
}

//Searches for the data in the Symbol Table
bool dataSearch(symbolTable st, char *name)
{    bool found = false;

	return found;
}

//Checks if the character is valid
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
	return i;
}
//Checks if there is a list
int *checkList(char *name)
{
    symbolTable *aux;
    char *nameCheck="teste";

    aux = root;
    
    while (aux != NULL) {
		if(name == nameCheck)
    		return 1;
		aux = aux->next;
    }
    return 0;
}

//Checks if string contains only Numbers
int checkNumber(const char *string)
{
	while (*string) {
        if (isdigit(*string++) == 0)
        {
			return 0;
		}
    }

    return 1;
}
//Checks if the user is trying to use a reserved word the wrong way
int testReserved(char *str)
{
	
	if(strstr(str,"programa") || strstr(str,"leia") || strstr(str,"escreva") || strstr(str,"se") || strstr(str,"senao") || strstr(str,"para") || strstr(str,"inteiro") || strstr(str,"caractere") ||strstr(str,"real") || strstr(str,"fim") )
	{
		printf("\nA palavra \"%s\" é uma palavra reservada!\n", str);
		system("pause");
	}
}

//Checks if there is a ";" where it supposed to be
int testSemi(const char *str)
{
  if(*str && str[strlen(str + 1)] == ';')
    return 0;
  else
    return 1;
}
