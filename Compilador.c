#include <stdio.h>
#include <stdlib.h>

char wordLst(*word, *nextWord);
typedef struct lineLst
{
	char line[200];
	int *nextLine, lineNum;
};

typedef struct wordLst
{
	char word[50];
	int *nxtWord;
} LINES;
	
int main() {

    FILE *f;
    char *word;
    int count = 0;
    f=fopen("test.txt","rt");
    l = (*LINES)malloc(sizeof(LINES));    

	if(f == NULL)
	{
		printf("Problems Finding File!");
	}
	else
	{
    	while((word=fgetc(f))!=EOF){
        	printf("%c",word);
        	count++;
    	}
	}
	
	printf("\n %i",count);

    fclose(f);
    return 0;
}


