#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE *f;
    char c;
    int count = 0;
    f=fopen("test.txt","rt");

	if(f == NULL)
	{
		printf("Problemas ao encontrar o arquivo!");
	}
	else
	{
    	while((c=fgetc(f))!=EOF){
        	printf("%c",c);
        	count++;
    	}
	}
	printf("\n %i",count);

    fclose(f);
    return 0;
}

struct variable()
{

}
