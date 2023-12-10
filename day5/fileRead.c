#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
#define MAX_FILE_LINES 200

int fileRead(char *fileName, char *lines[])
{
    int row = 0;
    FILE *fp;
    char   strInput[STR_MAX];
    int len=0;
    char *line;
   
   fp = fopen(fileName, "r");
   if(fp == NULL)
   {
      printf("Unable to open file[%s].\n", fileName);
      return -1;
   } 

   memset((void *)strInput,'\0',STR_MAX);
   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
       len = strlen(strInput);
       printf("len[%d], %s", len, strInput);
       if(len >= STR_MAX)
       {
         printf("Increase the array size\n");
         fclose(fp);
         return -2;//ERROR
       }
       printf("%d\n",__LINE__);
       if(row >= MAX_FILE_LINES)
       {
          printf("Increase the line size\n");
            fclose(fp);
           return -3;//ERROR
       }
       printf("%d\n",__LINE__);
       if(strInput[len-1] == '\n')
       {
            len--;
            strInput[len] = '\0';
       }
       printf("%d\n",__LINE__);
       line=malloc(sizeof(len));
       if(line == NULL)
       {
        printf("Unable to allocate memory for line after %d row", row);
        fclose(fp);
        return -4;
       }
       printf("%d\n",__LINE__);
       strcpy(line,strInput);
       lines[row] = line;
       printf("row[%d][%s]\n", row, line);
        row++;
   }
   fclose(fp);

   return row;

}
int main(int argc, char * argv[])
{
   FILE *fp;
   char   strInput[STR_MAX];
   char *lines[MAX_FILE_LINES];

   int row = 0;

   if(argc < 2)
   {
       printf("Invalid input\n");
       printf("Sample(./a.exe <input filename>)\n");
       return 1;
   }
    row = fileRead(argv[1], lines);

   printf("Total lines: %d\n", row);
   return 0;
}