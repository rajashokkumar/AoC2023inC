#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
#define MAX_LINES 1024


int fileRead(char *input, char **lines)
{
   FILE *fp;
   char strInput[STR_MAX];
   int len = 0;
   int row = 0;
 
   fp = fopen(input, "r");
   if(fp == NULL)
   {
      printf("Unable to open file[%s].\n", input);
      return -1;
   } 
   
   memset((void *)strInput,'\0',STR_MAX);
   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
       len = strlen(strInput);
       if(len >= STR_MAX)
       {
         printf("Increase the array size\n");
         return -2;//ERROR
       }
       if(strInput[len-1] == '\n')
       {
            len--;
            strInput[len] = '\0';
       }
       row++;
       if(row > MAX_LINES)
       {
        printf("More than  %d lines, increase line size\n",MAX_LINES);
        return -3;
       }
   }
   return row;
}


int main(int argc, char *argv[])
{
    char lines[MAX_LINES][STR_MAX];
    fileRead(argv[1], lines);
    return 0;
}