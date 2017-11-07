#include <stdio.h>
#include <stdlib.h>

//char wordLst(*word, *nextWord);
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
    printf(line);
}
free(line);    // dont forget to free heap memory
}


