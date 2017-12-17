#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>
#include <C:\Users\Lucas\Documents\GitHub\Compilador\lexica.h>


char *names[2] = {"var1", "var2"};
char *types[2] = {"int", "char"};
char *values[2] = {"1", "stephen"};
char *lines[200];
typedef struct list {
  char *name;
  char *type;
  char *value;
  char *sizeLimit;
  int line;
  struct list *next;
} symbolTable;

symbolTable *root = NULL, *leaf = NULL; 
symbolTable *insertSymbol(char *name, char *type, char *value, char *sizeLimit, int line);

bool checkVariableList(char *name);
bool dataSearch(symbolTable, char *name);

char read(char *line);
char checkVariable(char *line);
char *findValue(char *name);
char *removeSpaces (char *input);
char *splitChar(char *line, char *firstDelimiter, char *secondDelimiter);
char *insertVariables (char *input);

int checkChar(char *string, char *value);
int checkInsertVarName(char *name);
int checkList(char *name);
int checkNumber(const char *string);
int testReserved(char *str);

void createList(char *name, char *type, char *value, char *sizeLimit);
void equation();
void lineCount();
void printList();


int size = 0;
int lineNo = 1;
FILE* fh;

int main() {
	setlocale(LC_ALL, "PORTUGUESE");
	int i;
	fopen_s(&fh, "test.txt", "r");

	if (fh == NULL){
   		printf("O seguinte arquivo não existe: %s", "test.txt");
   		system("pause");
   		exit(0);
	}
	
	lineCount();
	equation();
/*
    for (i = 0; i < 2; i++)
    {
    	insertSymbol(names[i], types[i], values[i]);
    	printf("\nNome: %s, Tipo: %s, Valor: %s", st[i].name, st[i].type, st[i].value);
    	printf("%p",st[i]);
	}
	*/	
	
	
    printList();
	printf("\nQuantidade de bytes usado: %i",size);
	free(root);
}

//Inserts variables into the Symbol Table
symbolTable *insertSymbol(char *name, char *type, char *value, char *sizeLimit, int line)
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
    strncpy(leaf->sizeLimit, sizeLimit, strlen(sizeLimit)+1);
    
    leaf->line = line;
    leaf->next = NULL;
    
    size = size + sizeof(leaf->name);
    size = size + sizeof(leaf->value);
    size = size + sizeof(leaf->type);
    size = size + sizeof(leaf->sizeLimit);
    size = size + sizeof(leaf->line);
    size = size + sizeof(leaf);
    //printf("\n Nome: %s, Tipo: %s, Valor: %s Insert into table Successful!\n",name, type, value);
    return leaf;
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

//Leia function
char read(char *line)
{	
	char *token, *name="NULL";
	int aux = checkChar(line,",") + 1;
	
	testSemi(line,lineNo);
	
	if(strstr(splitChar(line,"(",")"),"inteiro") || strstr(splitChar(line,"(",")"),"caractere") || strstr(splitChar(line,"(",")"),"real"))
	{
		printf("\nERRO linha %i: Não pode haver declaração de variável dentro da função \"leia()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}
	
	if(strstr(line,"()") || strstr(line,"(,") || strstr(line,",)") || strstr(line,",,"))
	{
		printf("\nERRO linha %i: Poucos argumentos dentro da função \"leia()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}
	//printf("%i \n",aux);
	
	while(aux != 0)
	{
		
		name = "NULL";
		if(strstr(line,"#"))
		{	
			if(!strstr(splitChar(line,"#",","),"ERRO"))
		    	name = splitChar(line,"#",",");
		    else if(!strstr(splitChar(line,"#",")"),"ERRO"))
		    	name = splitChar(line,"#",")");
		}
		if(strstr(line,"="))
		{				
			printf("\nERRO linha %i: Não pode haver atribuição de valores através de \"=\" dentro da função\"leia()\"\n", lineNo);
	    	system("pause");
	    	exit(0);
		}		
		
				
		if(aux > 1)
		{
			line = splitChar(line,",",";");
			strcat(line, ";");
		}
		
		
	
		if(checkInsertVarName(name) == 0)
		{
			printf("\nERRO linha %i: Variável \"%s\" não declarada anteriormente\n", lineNo, name);
	    	system("pause");
	    	exit(0);	
		}
		aux--;
	}

	
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
    return variable[0];
}

//Find value based on name
char *findValue(char *name)
{
	symbolTable *st = (symbolTable *) malloc(sizeof(symbolTable));
	//char *auxC = "teste";
	int i = 1;
	st = root;
	
	while(st != NULL && st->name != NULL)
	{	
		if(strcmp(name,st->name) == 0)
		{
			return st->value;
		}
		else
		{
			st = st->next;
		}
	}
	
	free(st);
	return "Não Encontrado";
}

//For function
char forFn(char *line)
{	
	char *token, *name="NULL";
	int aux = checkChar(line,";");
	
	
	
	if(strstr(splitChar(line,"(",")"),"inteiro") || strstr(splitChar(line,"(",")"),"caractere") || strstr(splitChar(line,"(",")"),"real"))
	{
		printf("\nERRO linha %i: Não pode haver declaração de variável dentro da função \"para()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}
	
	if(strstr(line,"()") || strstr(line,"(,") || strstr(line,",)") || strstr(line,",,") || aux != 3)
	{
		printf("\nERRO linha %i: Poucos argumentos dentro da função \"para()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}

	
}
//Se function
char ifFn(char *line)
{	
	char *token, *name="NULL";
	
	
	
	if(strstr(splitChar(line,"(",")"),"inteiro") || strstr(splitChar(line,"(",")"),"caractere") || strstr(splitChar(line,"(",")"),"real"))
	{
		printf("\nERRO linha %i: Não pode haver declaração de variável dentro da função \"se()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}
	
	if(strstr(line,"()") || strstr(line,"(,") || strstr(line,",)") || strstr(line,",,"))
	{
		printf("\nERRO linha %i: Poucos argumentos dentro da função \"se()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}

	
}

//Remove spaces and useless data
char* removeSpaces (char* input)
{
    int i,j, aux = 1;
    char *output=input;
    
    for (i = 0, j = 0; i<strlen(input); i++,j++)
    {
    	if((input[i] == '>' || input[i] == '<') && (input[i+1] == ' '|| input[i+1] == '\t' || input[i+1] == 'n' ) && (input[i+2] == '=' || input[i+3] == '=' || input[i+4] == '=' )) 
    	{
    		printf("Não pode haver espaços entre <= e >=\n");
    		system("pause");
    		exit(0);
		}
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

	char *PATTERN1 = firstDelimiter;
    char *PATTERN2 = secondDelimiter;

    char *target = NULL;
    char *start, *end;

	
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

//Insert Variables
char *insertVariables (char *input)
{
	char *token, *name="NULL", *type="NULL", *value="NULL", *sizeLimit="NULL", splitVariable[strlen(input)], splitValue[strlen(input)];
	strcpy(splitVariable, input);
	strcpy(splitValue, input);
	int aux = checkChar(input,",") + 1;
	
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
			printf("ERRO na linha %i: Atribuição de variável deve receber tipo de valor inteiro, caractere ou real!", lineNo);
			system("pause");
		}
		
		testSemi(input,lineNo);
		
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
			  
				else if(!strstr(splitChar(input,"=",";"),"ERRO"))
			  		value = splitChar(input,"=",";");
			  	
				if(type != "caractere" && strstr(input,"\""))
				{
					printf("\nERRO na linha %i: Tipo %s não pode receber valor do tipo charactere!",lineNo, type );
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
					printf("\nERRO na linha %i: O campo aceita apenas valores numéricos entre \"[\" e \"]\"!", lineNo);
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
				printf("\nERRO na linha %i: O valor %s é maior do que o limite implicado de [%s]!",lineNo, value, sizeLimit);
			}
			
			testReserved(name);
			if(checkInsertVarName(name) == 1)
			{
				printf("\nERRO na linha %i: Variável de nome \"%s\" já foi inserido!\n",lineNo, name);
				system("pause");
				exit(0);
			}
			insertSymbol(name, type, value, sizeLimit, lineNo);
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

//Escreva function
char write(char *line)
{	
	char *token, *name="NULL", *auxValue="", *auxValue2="";
	int aux = checkChar(line,",") + 1;
	
	
	
	testSemi(line,lineNo);
	
	if(strstr(splitChar(line,"(",")"),"inteiro") || strstr(splitChar(line,"(",")"),"caractere") || strstr(splitChar(line,"(",")"),"real"))
	{
		printf("\nERRO linha %i: Não pode haver declaração de variável dentro da função \"escreva()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}
	
	if(strstr(line,"()") || strstr(line,"(,") || strstr(line,",)") || strstr(line,",,"))
	{
		printf("\nERRO linha %i: Poucos argumentos dentro da função \"escreva()\"\n", lineNo);
    	system("pause");
    	exit(0);
	}
	//printf("%i \n",aux);
	
	while(aux != 0)
	{
		
		name = "NULL";
		if(strstr(line,"#"))
		{	
			if(!strstr(splitChar(line,"#",","),"ERRO"))
		    	name = splitChar(line,"#",",");
		    else if(!strstr(splitChar(line,"#",")"),"ERRO"))
		    	name = splitChar(line,"#",")");
		}
		if(strstr(line,"=") && strstr(splitChar(line,"(",")"),"inteiro"))
		{				
			printf("\nERRO linha %i: Não pode haver atribuição de valores através de \"=\" dentro da função\"escreva()\"\n", lineNo);
	    	system("pause");
	    	exit(0);
		}		
		if(strstr(line,"\"") && !strstr(splitChar(line,"\"","\""),"ERRO"))
		{
			auxValue = splitChar(line,"\"","\"");
			strcat(auxValue, findValue(name));
			name = "NULL";
			line = splitChar(line,",",";");
			strcat(line, ";");
			aux--;
		}
		else
			strcat(auxValue, findValue(name));
				
		if(aux > 1)
		{
			line = splitChar(line,",",";");
			strcat(line, ";");
		}
				
	
		if(strcmp(name,"NULL") != 0 && checkInsertVarName(name) == 0)
		{
			printf("\nERRO linha %i: Variável \"%s\" não declarada anteriormente\n", lineNo, name);
	    	system("pause");
	    	exit(0);	
		}
		aux--;
	}
	//printf("\nValores da função \"Escreva()\": %s\n", auxValue);

	
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
			return 1;
		}
		else
		{
			st = st->next;
		}
	}
	
	free(st);
	return 0;
}

//Checks if there is a list
int checkList(char *name)
{
    symbolTable *aux = (symbolTable *) malloc(sizeof(symbolTable));
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
		exit(0);
	}
}


//Creates a list
void createList(char *name, char *type, char *value, char *sizeLimit)
{
	root = insertSymbol(name, type, value, sizeLimit, lineNo);
}

//Resposible for all equations
void equation()
{
	symbolTable *aux;
	symbolTable *aux2;
	char *name, *currentValueChar;
    int i=1;
    int *currentValue, finalValue;

    aux = root;
    aux2 = root;
      
	while (aux != NULL) 
	{
		if(aux->type == "caractere")
    		aux = aux->next;
		 if(strstr(aux->value,"#"))
		 {
		 	
		 	if(!strstr(splitChar(aux->value,"#","+"),"ERRO"))
		 		name = splitChar(aux->value,"#","+");
		 	if(!strstr(splitChar(aux->value,"#","-"),"ERRO"))
		 		name = splitChar(aux->value,"#","-");
		 	if(!strstr(splitChar(aux->value,"#","*"),"ERRO"))
		 		name = splitChar(aux->value,"#","*");
		 	if(!strstr(splitChar(aux->value,"#","/"),"ERRO"))
		 		name = splitChar(aux->value,"#","/");
		 	if(!strstr(splitChar(aux->value,"#","^"),"ERRO"))
		 		name = splitChar(aux->value,"#","^");
		 	while(aux2 != NULL)
		 	{
		 		if(strcmp(name,aux2->name) == 0)
		 		{
		 			if(aux->type != aux2->type)
		 			{
		 				printf("Erro, não é possível comparar tipo \"%s\" com \"%s\".",aux->type, aux2->type);
					}
					if(!strstr(splitChar(aux->value,"#","+"),"ERRO"))
					{
		 				name = splitChar(aux->value,"#","+");
		 				currentValueChar = splitChar(strcat(aux->value, ";"),"+",";");
						finalValue = atoi(aux2->value) + atoi(currentValueChar);
					}
					if(!strstr(splitChar(aux->value,"#","-"),"ERRO"))
					{
		 				name = splitChar(aux->value,"#","-");
		 				currentValueChar = splitChar(strcat(aux->value, ";"),"-",";");
						finalValue = atoi(aux2->value) - atoi(currentValueChar);
					}
					if(!strstr(splitChar(aux->value,"#","*"),"ERRO"))
					{
		 				currentValueChar = splitChar(strcat(aux->value, ";"),"*",";");
						finalValue = atoi(aux2->value) * atoi(currentValueChar);
					}
					if(!strstr(splitChar(aux->value,"#","/"),"ERRO"))
					{
		 				currentValueChar = splitChar(strcat(aux->value, ";"),"/",";");
						finalValue = atoi(aux2->value) / atoi(currentValueChar);
					}
					if(!strstr(splitChar(aux->value,"#","^"),"ERRO"))
					{
		 				currentValueChar = splitChar(strcat(aux->value, ";"),"^",";");
						//finalValue = (pow(atoi(aux2->value), atoi(currentValueChar)));
					}
					sprintf(aux->value, "%d", finalValue);
				}
				aux2 = aux2->next;
			}
		}
		i++;
    	aux = aux->next;
    }
    free(aux);
}

//Counts the lines and call necessary functions
void lineCount()
{
	//read line by line
	const size_t line_size = 300;
	char* line = malloc(line_size);
	while (fgets(line, line_size, fh) != NULL)
	{
		line = removeSpaces(line);
		if(lineNo == 1 && (strcmp(line,"programa")))
		{
			printf("\nERRO linha %i:  código deve inciar com \"programa\"\n",lineNo);
			system("pause");
			exit(0);
		}
		else
		{
			lines[lineNo] = line;
    		//printf(lines[lineNo]);
    		testLexic(line,lineNo);
    		if(strstr(line,"inteiro") || strstr(line,"caractere") || strstr(line,"real"))
    			checkVariable(lines[lineNo]);
    		if(strstr(line,"leia"))
    			read(lines[lineNo]);
    		if(strstr(line,"escreva"))
    			write(lines[lineNo]);
    		insertVariables(line);
    		if(strstr(line,"se"))
    			ifFn(lines[lineNo]);
    		if(strstr(line,"para"))
    			forFn(lines[lineNo]);
		}
		if(size > 350000000)
			printf("ERRO Memória Insuficiente");
    	
		lineNo++;
	}
	if(!strcmp(line,"fim"))
		testFinal(line,lineNo);
	else
	{
		printf("\nERRO linha %i:  código deve finalizar com \"fim\"\n", lineNo);
		system("pause");
		exit(0);
	}
	
	free(line);
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
       aux = aux->next; 
    }
    
    free(aux);
}

