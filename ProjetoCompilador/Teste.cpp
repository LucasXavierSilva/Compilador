#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stddef.h>
#include <stdbool.h>

int main(void) {
    char a[100] = "%20Conference%20successfully%20modified%200117246%20%20%20";
    char *p = strtok(a,"%");
    char n[20];
    while(p != NULL)
    {
      strcpy(n,p);
      p = strtok(NULL,"%");
      printf("%s\n",n);
    }
    return 0;
}
