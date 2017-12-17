#ifndef SINTATICA_H
#define SINTATICA_H

int braces = 0;
void testLexic(char *input, int number)
{
	testParentesis(input, number);
	testBrackets(input, number);
	testBraces(input, number);
	testCharacter(input, number);
	testQuotes(input,number);
	
	if(strstr(input,"#"))
		testVariable(input,number);
}


//Checks if braces are being properly opened and closed
int testBraces(char *input, int number)
{
	int i,j;
    
    for (i = 0; i<strlen(input); i++)
    {
        if (input[i] == '{')
		{    
			braces++;
		}                      
        else if (input[i] == '}')
        {        	
            braces--;
		}                                 
    }
}

//Checks if character is valid
int testCharacter(char *input, int *number)
{
	int i, aux = 1;
	char ch; 
    
    for (i = 0; i<strlen(input); i++)
    {
    	ch == input[i];
           
		/*if((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
	    {
	        printf("\n'%c' is alphabet.\n", input[i]);
	    }
	    else if(input[i] >= '0' && input[i] <= '9')
	    {
	        printf("\n'%c' is digit.\n", input[i]);
	    }
	    else 
	    {
	        printf("\n'%c' is special character.\n", input[i]);
	    }*/
	    if(input[i] == '\"')
	    	aux *= -1;
	   	if(input[i] < 10 && aux > 0)
	    {
	    	printf("\nERRO linha %i: Caractere não reconhecido \"%c\"\n", number, input[i]);
    		system("pause");
    		exit(0);
	    	
		}
		
	}                              
}

//Checks if braces are being properly opened and closed
int testBrackets(char *input, int number)
{
	int i, bracket = 0;    
    
    for (i = 0; i<strlen(input); i++)
    {
        if (input[i] == '[')
		{    
			bracket++;
		}                      
        else if (input[i] == ']')
        {        	
            bracket--;
		}                                 
    }
    if(bracket > 0)
    {
    	printf("\nERRO linha %i: Espera-se %i \"]\" antes do \";\"\n", number, bracket);
    	system("pause");
    	exit(0);
	}
    else if(bracket < 0)
    {
    	bracket = bracket*-1;
    	printf("\nERRO linha %i: Espera-se %i \"[\" antes do \";\"\n", number, bracket);
    	system("pause");
    	exit(0);
	}
}

int testFinal(char *input, int number)
{
	
    if(braces > 0)
    {
    	printf("\nERRO linha %i: Espera-se %i \"}\" após a abertura de chaves!\n", number, braces);
    	system("pause");
    	exit(0);
	}
    else if(braces < 0)
    {
    	braces = braces*-1;
    	printf("\nERRO linha %i: Espera-se %i \"{\" antes da abertura de chaves!\n", number, braces);
    	system("pause");
    	exit(0);
	}
}

//Checks if braces are being properly opened and closed
int testParentesis(char *input, int *number)
{
	int i, parentesis = 0;
    
    for (i = 0; i<strlen(input); i++)
    {
        if (input[i] == '(')
		{    
			parentesis++;
		}                      
        else if (input[i] == ')')
        {        	
            parentesis--;
		}                                 
    }
    if(parentesis > 0)
    {
    	printf("\nERRO linha %i: Espera-se %i \")\" antes do \";\"\n", number, parentesis);
    	system("pause");
    	exit(0);
	}
    else if(parentesis < 0)
    {
    	parentesis = parentesis*-1;
    	printf("\nERRO linha %i: Espera-se %i \"(\"antes do \";\"\n", number, parentesis);
    	system("pause");
    	exit(0);
	}
}

//Checks if braces are being properly opened and closed
int testQuotes(char *input, int *number)
{
	int i, quotes = 1;
    
    for (i = 0; i<strlen(input); i++)
    {
        if (input[i] == '"')
		{    
			quotes *= -1;
		}
    }
    if(quotes == -1)
    {
    	printf("\nERRO linha %i: Espera-se  \"aspas\" antes do \";\"\n", quotes);
    	system("pause");
    	exit(0);
	}
}

int testVariable(char *input, int number)
{
	int i;
    
    for (i = 0; i<strlen(input); i++)
    {
        if (input[i] == '#' && !((input[i++] >= 'a' && input[i++] <= 'z') || (input[i++] >= 'A' && input[i++] <= 'Z')))
		{			
	    	printf("\nERRO linha %i: Espera-se um caractere após \"#\"\n", number);
	    	system("pause");
	    	exit(0);
		}
    }
}

//Checks if there is a ";" where it supposed to be
int testSemi(const char *str, int number)
{
  if(*str && str[strlen(str + 1)] == ';')
  {
    return 0;
  }
  else
  {
  	printf("\nERRO linha %i: A linha deve encerrar com \";\"\n", number, str);
    system("pause");
   	exit(0);
  }
  return 1;
}
#endif
