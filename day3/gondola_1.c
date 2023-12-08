#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 512

typedef struct _nums
{
    int num;
    int row;
    int start_col;
    int end_col;
    struct _nums *next;
} NUMS;

int symbol[100][100];
int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int len = 0;
   int row = 0;
   int col = 0;

    //fp = fopen("input_1.txt", "r");
   fp = fopen("sample_1.txt", "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
       len = strlen(strInput);
       if(strInput[len-1] == '\n')
       {
            len--;
            strInput[len] = '\0';
       }
       //printf("%s\n", strInput);
       col = 0;
       while(strInput[col] != '\0')
       {
           if(strInput[col] != '.')
           {
             if ((strInput[col] >= '0') && (strInput[col] <= '9'))
             {
                //printf("Num [%c] row:%d col:%d\n", strInput[col], row, col);
             }
             else
             {
                printf("Char [%c] row:%d col:%d\n", strInput[col], row, col);
             }
                
           }
          col++;
       }

    row++;
   }
   return 0;
}