#include<string.h>
#include <stdlib.h>
#include <stdio.h>

#define STR_MAX 256

int findNum(char *input)
{
   int firstNum = -1;
   int lastNum = -1;
   int final = 0;
    int i = 0;

   while(input[i] != '\0')
   {
      if( input[i] >= '0' && input[i] <= '9')
      {
         if(firstNum == -1)
            firstNum = input[i] - '0';
         lastNum = input[i] - '0';
      }
      i++;
   }
   final = firstNum * 10 + lastNum;
   return final;
}

int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int total  = 0;
   int num = 0;

   fp = fopen("input_1.txt", "r");
   //fp = fopen("sample_1.txt", "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
        num = findNum(strInput);
        //printf("num = %d str=%s", num, strInput);
        total = total + num;
        memset((void *)strInput,'\0',STR_MAX);
   }
   fclose(fp);
   printf("\nTotal = %d\n", total);
   return 0;
}
